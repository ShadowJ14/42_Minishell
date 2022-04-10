/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 13:06:29 by rramos            #+#    #+#             */
/*   Updated: 2022/04/10 15:52:23 by rramos           ###   ########.fr       */
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

void	test_print_commands(t_command *command)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (command[++i].command)
	{
		j = -1;
		print_message("(debug) command ");
		print_message(ft_itoa(i));
		print_message(": ");
		print_message(command[i].command);
		print_message(" args:\n");
		print_message("(debug) ");
		while (command[i].args[++j])
		{
			print_message(command[i].args[j]);
			print_message(" ");
		}
		print_message("link: ");
		print_message(ft_itoa(command[i].chain));
		print_message("\n");
	}
}

int	main(int amount_of_program_arguments, char **program_arguments, \
	char **environment)
{
	t_environment_element	*environment_linked_list;
	t_terminal				terminal;
	t_command				*command;
	char					*builtin_funcs[BUILTIN_FUNCS_NB];
	char					*input;

	(void)amount_of_program_arguments;
	(void)program_arguments;
	handle_signals();
	environment_linked_list = format_environment(environment);
	open_terminal(&terminal);
	set_builtin_funcs(builtin_funcs);
	while (true)
	{
		input = read_input_until_new_line(terminal);
		print_message("(debug) input: ");
		print_message(input);
		print_message("\n");
		command = msh_split_line(input);
		test_print_commands(command);
		msh_execute(command, builtin_funcs, &environment_linked_list);
	}
	(void)environment_linked_list;
	return (EXIT_SUCCESS);
}
