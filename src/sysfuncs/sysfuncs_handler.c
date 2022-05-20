/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sysfuncs_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:07:00 by lprates           #+#    #+#             */
/*   Updated: 2022/05/20 23:31:36 by lprates          ###   ########.fr       */
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
			return (cmd);
		ret_access = access(func, X_OK);
		if (ret_access == 0)
			return (func);
		free(cmd);
		if (*ret)
			ret++;
	}
	return (NULL);
}

/*
** funtions that handles the redirection in and append in to file
**
*/
int	send_output(int pipe, char *path, int chain)
{
	char	reading_buf[1];
	int		file;
	int		mode;

	if (chain == APPEND)
		mode = O_RDWR | O_APPEND;
	else
		mode = O_RDWR | O_TRUNC;
	file = open(path, mode);
	if (file == -1)
		file = open(path, mode | O_CREAT, 0666);
	if (file == -1)
	{
		perror(ft_strjoin("minishell: ", path));
		return (EXIT_FAILURE);
	}
	while (read(pipe, reading_buf, 1) > 0)
	{
		write(file, reading_buf, 1);
	}
	close(file);
	return (EXIT_SUCCESS);
}

int	do_pipe(int *pipe, t_cmd to_cmd)
{
	char	*cmd;
	int		pid;
	int		status;

	cmd = check_sysfunction(to_cmd.exec);
	if (cmd)
	{
		dup2(*pipe, 0);
		pid = fork();
		if (!pid)
		{
			if (execve(cmd, to_cmd.args, NULL) == -1)
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
		}
		free(cmd);
	}
	else
		printf("cmd '%s' not found.\n", to_cmd.exec);
	return (EXIT_SUCCESS);
}
