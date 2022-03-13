/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 13:06:29 by rramos            #+#    #+#             */
/*   Updated: 2022/03/13 16:44:02 by rramos           ###   ########.fr       */
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

	(void)amount_of_program_arguments;
	(void)program_arguments;
	handle_signals();
	environment_linked_list = format_environment(environment);
	open_terminal(&terminal);
	g_global.input = NULL;
	while (true)
	{
		print_message("minishell: ");
		read_input_until_new_line(terminal);
		handle_commands();
	}
	return (EXIT_SUCCESS);
}
