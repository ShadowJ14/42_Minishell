/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 22:05:21 by rramos            #+#    #+#             */
/*   Updated: 2022/03/20 14:25:19 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Work in progress. The function needs to be improved for when there are spaces,
quotes, and such.
*/

static void	handle_exit_command(void)
{
	if (g_global.input[0] == 'e' && g_global.input[1] == 'x' \
		&& g_global.input[2] == 'i' && g_global.input[3] == 't' \
		&& (g_global.input[4] == ' ' || g_global.input[4] == '\0'))
	{
		free_memory(&g_global.input);
		exit(EXIT_SUCCESS);
	}
}

//? should be return code
int	msh_execute(t_command *command, char **builtin_funcs, char **environment)
{
	int	return_code;

	return_code = builtin(command, builtin_funcs, environment);
	if (!return_code)
		return_code = exec_sysfunction(command[0]);
	return (1);
}

void	handle_commands(t_command *cmd, char **env, char **builtin_funcs)
{
	msh_execute(cmd, builtin_funcs, env);
	handle_exit_command();
}
