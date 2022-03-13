/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_funcs_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:25:31 by lprates           #+#    #+#             */
/*   Updated: 2022/03/13 17:36:11 by lprates          ###   ########.fr       */
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

/* implements echo with -n option builtin
*/

void	do_echo(char **args)
{
	int	idx;

	if (args[1] && !ft_strcmp(args[1], "-n"))
	{
		idx = 1;
		while (args[++idx])
		{
			if (idx != 2)
				write(1, " ", 1);
			write(1, args[idx], ft_strlen(args[idx]));
		}
	}
	else
	{
		idx = 0;
		while (args[++idx])
		{
			if (idx != 1)
				write(1, " ", 1);
			write(1, args[idx], ft_strlen(args[idx]));
		}
		write(1, "\n", 1);
	}
}

/* implements cd builtin
** returns 1 on success
** returns 0 on failure
** needs to update old pwd because of cd -
*/
int	do_cd(char *path)
{
	if (!chdir(path))
		return (1);
	write(1, "cd: no such file or directory: ", 32);
	write(1, path, ft_strlen(path));
	write(1, "\n", 2);
	return (0);
}

void	do_exit(char **args)
{
	if (args[1])
		exit(ft_atoi(args[1]));
	else
		exit(1);
}

/* hub for executing builtin functions
** returns 1 on success
** returns 0 on failure
** needs error handling
*/
int	execute_builtins(char *cmd, char **args, char **environ)
{
	if (!ft_strcmp(cmd, "cd"))
		do_cd(args[1]);
	if (!ft_strcmp(cmd, "pwd"))
		printf("current path is: %s\n", getcwd(NULL, 0));
	if (!ft_strcmp(cmd, "echo"))
		do_echo(args);
	/*if (cmd == "export")
	if (cmd == "unset")*/
	if (!ft_strcmp(cmd, "env"))
		while (*environ)
			printf("%s\n", *(environ++));
	if (!ft_strcmp(cmd, "exit"))
		do_exit(args);
	return (1);
}

int	builtin(t_command *cmd, char **builtin_funcs, char **environ)
{
	int	idx;

	idx = -1;
	while (++idx < BUILTIN_FUNCS_NB)
	{
		if (!ft_strcmp(cmd->command, builtin_funcs[idx]))
		{
			execute_builtins(cmd->command, cmd->args, environ);
			return (1);
		}
	}
	return (0);
}
