/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sysfuncs_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:07:00 by lprates           #+#    #+#             */
/*   Updated: 2022/02/27 18:32:45 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_sysfunction(char *func)
{
	char *envs;
	char **ret;
	char *cmd;
	int ret_access;

	envs = getenv("PATH");
	ret = ft_split(envs, ':');
	while (*ret)
	{
		cmd = ft_strjoin(*ret, ft_strjoin("/", func));
		ret_access = access(cmd, X_OK);
		if (ret_access == 0)
			return (cmd);
		free(cmd);
		ret++;
	}
	return (NULL);
}

int	exec_sysfunction(char **args)
{
	int	pid;
	int	status;
	char *cmd;

	cmd = check_sysfunction(args[0]);
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
	return (1);
}
