/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_funcs_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:25:31 by lprates           #+#    #+#             */
/*   Updated: 2022/02/27 18:46:48 by lprates          ###   ########.fr       */
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

int	execute_builtins(char *cmd)
{
}

int	builtin(char *cmd, char **builtin_funcs, char **args)
{
	int idx;

	idx = -1;
	while (++idx < BUILTIN_FUNCS_NB)
	{
		if (!ft_strcmp(cmd, builtin_funcs[idx]))
		{
			execute_builtins(cmd);
			return (1);
		}
	}
	return (0);
}
