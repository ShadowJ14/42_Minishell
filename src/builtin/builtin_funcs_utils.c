/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_funcs_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:25:31 by lprates           #+#    #+#             */
/*   Updated: 2022/03/05 14:51:40 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_builtin_funcs(char **builtin_funcs)
{
	builtin_funcs[0] = "cd";
	builtin_funcs[1] = "pwd";
	builtin_funcs[2] = "echo";
	builtin_funcs[3] = "export";
	builtin_funcs[4] = "unset";
	builtin_funcs[5] = "env";
	builtin_funcs[6] = "exit";
}

int	execute_builtins(char *cmd, char **args)
{
	char	*path;
	extern char **environ;

	if (!ft_strcmp(cmd, "cd"))
		chdir(args[1]);
	if (!ft_strcmp(cmd, "pwd"))
	{
		path = getcwd(NULL, 0);
		printf("current path is: %s\n", path);
	}
	if (!ft_strcmp(cmd, "echo"))
	{
		if (!ft_strcmp(args[1], "-n"))
			write(1, args[2], ft_strlen(args[2]));
		else
		{
			write(1, args[1], ft_strlen(args[1]));
			write(1, "\n", 1);
		}
			//printf("%s\n", args[1]);
	}
	/*if (cmd == "export")
	if (cmd == "unset")*/
	if (!ft_strcmp(cmd, "env"))
		while (*environ)
			printf("%s\n", *(environ++));
	if (!ft_strcmp(cmd, "exit"))
	{
		if (args[1])
			exit(ft_atoi(args[1]));
		else
			exit(1);
	}
	(void)path;
	return (1);
}

int	builtin(char *cmd, char **builtin_funcs, char **args)
{
	int idx;

	idx = -1;
	while (++idx < BUILTIN_FUNCS_NB)
	{
		if (!ft_strcmp(cmd, builtin_funcs[idx]))
		{
			execute_builtins(cmd, args);
			return (1);
		}
	}
	return (0);
}
