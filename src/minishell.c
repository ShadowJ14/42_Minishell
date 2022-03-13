/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 04:07:52 by lprates           #+#    #+#             */
/*   Updated: 2022/03/13 16:58:53 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_execute(t_command *cmd, char **builtin_funcs, char **environ)
{
	int	return_code;

	return_code = builtin(cmd, builtin_funcs, environ);
	if (!return_code)
		return_code = exec_sysfunction(cmd[0].command, cmd[0].args);
	//? should be return code
	return (1);
}

t_command	*msh_split_line(char *line)
{
	t_command	*cmd;

	cmd = local_split(line, "|<>");
	if (!cmd)
		return (NULL);
	return (cmd);
}

char	*msh_readline(void)
{
	char	*line;

	line = readline("Enter a command> ");
	if (line && *line)
		add_history(line);
	//! unnecessary for now
	// if (!ft_strcmp(line, "history"))
	// {
	// 	printf("Teste\n");
	// 	//rl_redisplay();
	// }
	return (line);
}

void	msh_loop(char **builtin_funcs, char **environ)
{
	char		*line;
	t_command	*cmd;
	int			status;

	status = 1;
	while (status)
	{
		line = msh_readline();
		cmd = msh_split_line(line);
		if (!cmd)
		{
			printf("Erro caralho!\n");
			return ;
		}
		status = msh_execute(cmd, builtin_funcs, environ);
		free(line);
		free(cmd);
	}
}

int	main(int ac, char **av, char **environ)
{
	char	*builtin_funcs[BUILTIN_FUNCS_NB];

	(void)ac;
	(void)av;
	set_builtin_funcs(builtin_funcs);
	msh_loop(builtin_funcs, environ);
}
