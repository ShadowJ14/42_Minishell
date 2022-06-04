/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 13:06:29 by rramos            #+#    #+#             */
/*   Updated: 2022/05/22 23:46:25 by lprates          ###   ########.fr       */
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

static void	expand_env_in_args(t_cmd *cmd)
{
	int			j;

	j = -1;
	while (cmd->exec)
	{
		j = -1;
		while (cmd->args[++j])
		{
			printf("before arg%i:%s\n", j, cmd->args[j]);
			cmd->args[j] = word_modif_two(cmd->args[j], NONE, NONE);
			printf("arg%i:%s\n", j, cmd->args[j]);
		}
		cmd++;
	}
}

void	init_shell(t_terminal *terminal, char **environment)
{
	t_env_elem	*env_linklist;

	env_linklist = format_environment(environment);
	env_singleton(env_linklist);
	update_shlvl();
	open_terminal(terminal);
	handle_signals();
}

void	activate_controlchars(t_terminal *terminal)
{
	terminal->attributes_new = terminal->attributes;
	terminal->attributes_new.c_lflag &= ~(ICANON | ECHO);
	terminal->attributes_new.c_cc[VMIN] = 1;
	terminal->attributes_new.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal->attributes_new);
}

int	main(int amount_of_program_arguments, char **program_arguments, \
	char **environment)
{
	t_terminal	terminal;
	t_cmd		*cmd;
	char		*input;

	(void)amount_of_program_arguments;
	(void)program_arguments;
	init_shell(&terminal, environment);
	g_exit_code = 0;
	while (true)
	{
		//open_terminal(&terminal);
		input = read_input_until_new_line();
		if (input != NULL)
		{
			//activate_controlchars(&terminal);
			printf("input: %s\n", input);
			cmd = msh_split_line(input);
			expand_env_in_args(cmd);
			msh_execute(cmd);
			free(input);
			free_all(NULL);
		}
	}
	free_all("ENV");
	return (EXIT_SUCCESS);
}
