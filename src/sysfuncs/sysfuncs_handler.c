/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sysfuncs_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:07:00 by lprates           #+#    #+#             */
/*   Updated: 2022/03/13 16:54:55 by lprates          ###   ########.fr       */
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

int	exec_sysfunction(char *command, char **args)
{
	int		pid;
	int		status;
	char	*cmd;
	int		my_pipe[2];

	if (pipe(my_pipe) == -1)
	{
		perror("Error creating pipe");
	}
	cmd = check_sysfunction(command);
	if (cmd)
	{
		pid = fork();
		if (!pid)
		{
			close(my_pipe[0]);
			dup2(my_pipe[1], 1);
			if (execve(cmd, args, NULL) == -1)
			{
				perror("msh");
				exit(EXIT_FAILURE);
			}
		}
		else if (pid < 0)
			perror("msh");
		else
		{
			waitpid(pid, &status, WUNTRACED);
			while (!WIFEXITED(status) && !WIFSIGNALED(status))
				waitpid(pid, &status, WUNTRACED);
			close(my_pipe[1]);
			char reading_buf[1];
			while(read(my_pipe[0], reading_buf, 1) > 0)
			{
				write(1, reading_buf, 1);
			}
		}
		free(cmd);
	}
	return (0);
}
