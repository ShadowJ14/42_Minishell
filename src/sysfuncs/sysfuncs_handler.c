/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sysfuncs_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:07:00 by lprates           #+#    #+#             */
/*   Updated: 2022/03/20 14:31:20 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_sysfunction(char *func)
{
	char	*envs;
	char	**ret;
	char	*cmd;
	int		ret_access;

	envs = getenv("PATH");
	ret = ft_split(envs, ':');
	while (*ret)
	{
		cmd = ft_strjoin(*ret, ft_strjoin("/", func));
		ret_access = access(cmd, X_OK);
		if (ret_access == 0)
		{
			return (cmd);
		}
		free(cmd);
		if (*ret)
			ret++;
	}
	return (NULL);
}

int	append_output(int pipe)
{
	char	reading_buf[1];
	int		file;

	file = open("./test.txt", O_RDWR);
	while (read(file, reading_buf, 1) > 0)
		;
	while (read(pipe, reading_buf, 1) > 0)
	{
		write(file, reading_buf, 1);
	}
	close(file);
	return (EXIT_SUCCESS);
}

int	exec_sysfunction(t_command command)
{
	int		pid;
	int		status;
	char	*cmd;
	int		my_pipe[2];

	if (pipe(my_pipe) == -1)
	{
		perror("Error creating pipe");
	}
	cmd = check_sysfunction(command.command);
	if (cmd)
	{
		pid = fork();
		if (!pid)
		{
			close(my_pipe[0]);
			dup2(my_pipe[1], 1);
			if (execve(cmd, command.args, NULL) == -1)
			{
				perror("msh");
				exit(EXIT_FAILURE);
			}
			close(my_pipe[1]);
		}
		else if (pid < 0)
			perror("msh");
		else
		{
			waitpid(pid, &status, WUNTRACED);
			while (!WIFEXITED(status) && !WIFSIGNALED(status))
				waitpid(pid, &status, WUNTRACED);
			close(my_pipe[1]);
			if (command.chain == APPENDO)
				append_output(my_pipe[0]);
			else
			{
				char	reading_buf[1];
				while (read(my_pipe[0], reading_buf, 1) > 0)
					write(1, reading_buf, 1);
			}
			close(my_pipe[0]);
			ft_putstr("parent out pipe closing\n");
		}
		free(cmd);
	}
	return (0);
}

/*
int	exec_sysfunction(char *command, char **args)
{
	int		pid;
	int		status;
	char	*cmd;

	cmd = check_sysfunction(command);
	if (cmd)
	{
		pid = fork();
		if (!pid)
		{
			if (execve(cmd, args, NULL) == -1)
			{
				perror("msh");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			waitpid(pid, &status, WUNTRACED);
			while (!WIFEXITED(status) && !WIFSIGNALED(status))
				waitpid(pid, &status, WUNTRACED);
		}
		free(cmd);
	}
	return (0);
}
*/
