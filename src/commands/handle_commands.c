/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 22:05:21 by rramos            #+#    #+#             */
/*   Updated: 2022/04/09 15:20:42 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//? should be return code
int	msh_execute(t_command *command, char **builtin_funcs, t_environment_element *environment_linked_list)
{
	//int	return_code;

	//return_code = builtin(command, builtin_funcs, environment_linked_list);
	//if (!return_code)
		exec_sysfunction(command, builtin_funcs, environment_linked_list);
	return (1);
}

int	msh_execute_two(t_command *command, char **builtin_funcs, t_environment_element *environment_linked_list)
{
	int	return_code;

	return_code = builtin(command, builtin_funcs, environment_linked_list);
	if (!return_code)
		return_code = exec_sysfunction_two(command);
	
	return (1);
}

int	exec_sysfunction_two(t_command *command)
{
	char	*cmd;

	cmd = check_sysfunction(command->command);
	if (cmd)
	{
		if (execve(cmd, command->args, NULL) == -1)
		{
			perror("msh");
			exit(EXIT_FAILURE);
		}
		free(cmd);
	}
	else
		printf("Command '%s' not found.\n", command->command);
	return (0);
}
