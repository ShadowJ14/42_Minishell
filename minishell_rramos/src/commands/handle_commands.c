/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 22:05:21 by rramos            #+#    #+#             */
/*   Updated: 2022/03/26 12:30:51 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}
