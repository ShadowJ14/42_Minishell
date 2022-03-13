/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 13:06:29 by rramos            #+#    #+#             */
/*   Updated: 2022/03/13 21:48:12 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// environment[0] = "PATH=" + getenv("PATH");

/*
To debug the code while the program is running, have this file active (opened
with the window focused), go to the "Run and Debug" tab on the left, then click
the "Start Debugging" button (green arrow icon) on the top.
Installed the "C/C++" extension ("C/C++ IntelliSense, debugging, and code
browsing.") and setted up the "launch.json" the "tasks.json" files in the folder.
*/

int	main(int amount_of_program_arguments, char **program_arguments, \
	char **environment)
{
	t_environment_element	*environment_linked_list;
	t_terminal				terminal;
	t_command				*command;
	char					*builtin_funcs[BUILTIN_FUNCS_NB];

	(void)amount_of_program_arguments;
	(void)program_arguments;
	handle_signals();
	environment_linked_list = format_environment(environment);
	open_terminal(&terminal);
	g_global.input = NULL;
	set_builtin_funcs(builtin_funcs);
	while (true)
	{
		read_input_until_new_line(terminal);
		printf("input: %s\n", g_global.input);
		command = msh_split_line(g_global.input);
		printf("test: %s args: %s\n", command[0].command, command[0].args[0]);
		printf("test2: %s\n args %s\n", command[1].command, command[1].args[0]);
		handle_commands(command, environment, builtin_funcs);
	}
	return (EXIT_SUCCESS);
}
