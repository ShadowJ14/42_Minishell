/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 13:06:29 by rramos            #+#    #+#             */
/*   Updated: 2022/04/10 20:00:27 by lprates          ###   ########.fr       */
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

static void	test_print_commands(t_command *command, t_environment_element \
		*environment_linked_list)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (command[++i].command)
	{
		j = -1;
		printf("command%i: %s args: ", i, command[i].command);
		while (command[i].args[++j])
		{
			if (ft_strchr(command[i].args[j], '$'))
				command[i].args[j] = expand_env_var(environment_linked_list, ft_strchr(command[i].args[j], '$') + 1);
			printf("%s ", command[i].args[j]);
		}
		printf("link: %i\n", command[i].chain);
	}
}

int	main(int amount_of_program_arguments, char **program_arguments, \
	char **environment)
{
	t_environment_element	*environment_linked_list;
	t_terminal				terminal;
	t_command				*command;
	char					*input;

	(void)amount_of_program_arguments;
	(void)program_arguments;
	handle_signals();
	environment_linked_list = format_environment(environment);
	open_terminal(&terminal);
	//g_global.input = NULL;
	g_exit_code = 0;
	while (true)
	{
		input = read_input_until_new_line(terminal);
		if (input)
		{
			printf("input: %s\n", input);
			command = msh_split_line(input);
			test_print_commands(command, environment_linked_list);
			msh_execute(command, environment_linked_list);
		}
	}
	(void) environment_linked_list;
	return (EXIT_SUCCESS);
}
