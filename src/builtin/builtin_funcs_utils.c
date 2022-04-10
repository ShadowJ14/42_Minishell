/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_funcs_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:25:31 by lprates           #+#    #+#             */
/*   Updated: 2022/04/10 17:18:57 by lprates          ###   ########.fr       */
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

/* hub for executing builtin functions
** returns 1 on success
** returns 0 on failure
** needs error handling
** export and unset missing
*/
int	execute_builtins(char *cmd, char **args, \
	t_environment_element *environment_linked_list)
{
	if (!ft_strcmp(cmd, "cd"))
		do_cd(args[1], environment_linked_list);
	if (!ft_strcmp(cmd, "pwd"))
		printf("current path is: %s\n", getcwd(NULL, 0));
	if (!ft_strcmp(cmd, "echo"))
		do_echo(args);
	if (!ft_strcmp(cmd, "export"))
		do_export(args, &environment_linked_list);
	if (!ft_strcmp(cmd, "unset"))
		do_unset(args, &environment_linked_list);
	if (!ft_strcmp(cmd, "env"))
		print_export(environment_linked_list);
	if (!ft_strcmp(cmd, "exit"))
		do_exit(args);
	return (1);
}

int	is_builtin(t_command *cmd, \
	t_environment_element *environment_linked_list)
{
	int		idx;
	char	*builtin_funcs[BUILTIN_FUNCS_NB];


	(void) environment_linked_list;
	set_builtin_funcs(builtin_funcs);
	idx = -1;
	while (++idx < BUILTIN_FUNCS_NB)
	{
		if (!ft_strcmp(cmd->command, builtin_funcs[idx]))
			return (1);
	}
	return (0);
}
