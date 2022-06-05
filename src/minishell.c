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

void	init_shell(char **environment)
{
	t_env_elem	*env_linklist;

	if (!isatty(STDIN_FILENO))
		print_error_message("Wrong or no atty.\n");
	env_linklist = format_environment(environment);
	env_singleton(env_linklist);
	update_shlvl();
	handle_signals();
}

char	*missing_quote(void)
{
	printf("minishell: missing quote\n");
	return (NULL);
}

char	*check_str(char *s)
{
	char	quote;
	char	tmp;
	char	*ret;

	ret = s;
	if (!s)
		return (NULL);
	while (*s)
	{
		tmp = 0;
		if (ft_strchr("\"\'", *s))
			tmp = *s;
		if (tmp)
		{
			quote = 0;
			s++;
			while (*s && *s != tmp)
				s++;
			if (*s == tmp)
				quote = 1;
			if (!quote)
				return (missing_quote());
		}
		if (*s)
			s++;
	}
	return (ret);
}

int	main(int amount_of_program_arguments, char **program_arguments, \
	char **environment)
{
	t_cmd		*cmd;
	char		*input;

	(void)amount_of_program_arguments;
	(void)program_arguments;
	init_shell(environment);
	g_exit_code = 0;
	while (true)
	{
		termios_change(false);
		input = read_input_until_new_line();
		input = check_str(input);
		if (input != NULL)
		{
			termios_change(true);
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
