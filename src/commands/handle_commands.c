/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 22:05:21 by rramos            #+#    #+#             */
/*   Updated: 2022/03/26 17:41:35 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//? should be return code
int	msh_execute(t_command *command, char **builtin_funcs, t_environment_element **environment_linked_list)
{
	int	return_code;

	return_code = builtin(command, builtin_funcs, environment_linked_list);
	if (!return_code)
		return_code = exec_sysfunction(command[0]);
	return (1);
}
