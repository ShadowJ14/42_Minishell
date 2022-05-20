/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_funcs_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:25:31 by lprates           #+#    #+#             */
/*   Updated: 2022/05/21 00:11:14 by lprates          ###   ########.fr       */
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
int	execute_builtins(t_cmd *cmd, \
	t_env_elem *env_linklist, pid_t *pid, int fd)
{
	if (!ft_strcmp(cmd->exec, "cd"))
		do_cd(cmd->args[0], env_linklist);
	if (!ft_strcmp(cmd->exec, "pwd"))
		ft_built_in_pwd_fd(fd);
	if (!ft_strcmp(cmd->exec, "echo"))
		do_echo(cmd->args, fd);
	if (!ft_strcmp(cmd->exec, "export"))
		do_export(cmd->args, &env_linklist);
	if (!ft_strcmp(cmd->exec, "unset"))
		do_unset(cmd->args, &env_linklist);
	if (!ft_strcmp(cmd->exec, "env"))
		print_export(env_linklist);
	if (!ft_strcmp(cmd->exec, "exit"))
		do_exit(cmd->args, pid);
	return (1);
}

int	is_builtin(t_cmd *cmd)
{
	int		idx;
	char	*builtin_funcs[BUILTIN_FUNCS_NB];

	set_builtin_funcs(builtin_funcs);
	idx = -1;
	while (++idx < BUILTIN_FUNCS_NB)
	{
		if (!ft_strcmp(cmd->exec, builtin_funcs[idx]))
			return (1);
	}
	return (0);
}
