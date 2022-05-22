/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 13:06:29 by rramos            #+#    #+#             */
/*   Updated: 2022/05/22 21:51:07 by lprates          ###   ########.fr       */
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

static void	expand_env_in_args(t_cmd *cmd, t_env_elem \
		*env_linklist)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = -1;
	tmp = NULL;
	while (cmd[++i].exec)
	{
		j = -1;
		printf("cmd%i: %s args: ", i, cmd[i].exec);
		while (cmd[i].args[++j])
		{
			cmd[i].args[j] = word_modif_two(cmd[i].args[j], NONE, NONE, env_linklist);
			printf("%s ", cmd[i].args[j]);
		}
		printf("link: %i \n", cmd[i].chain);
	}
}

int	main(int amount_of_program_arguments, char **program_arguments, \
	char **environment)
{
	t_env_elem	*env_linklist;
	t_terminal	terminal;
	t_cmd		*cmd;
	char		*input;

	(void)amount_of_program_arguments;
	(void)program_arguments;
	handle_signals();
	env_linklist = format_environment(environment);
	open_terminal(&terminal);
	g_exit_code = 0;
	while (true)
	{
		input = read_input_until_new_line(terminal);
		if (input != NULL)
		{
			printf("input: %s\n", input);
			cmd = msh_split_line(input);
			expand_env_in_args(cmd, env_linklist);
			msh_execute(cmd, env_linklist);
		}
	}
	(void)env_linklist;
	return (EXIT_SUCCESS);
}
