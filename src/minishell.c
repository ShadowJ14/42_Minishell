/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 04:07:52 by lprates           #+#    #+#             */
/*   Updated: 2022/03/12 19:04:57 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_execute(t_command *cmd, char **builtin_funcs)
{
	int	return_code;

	return_code = builtin(cmd[0].command, builtin_funcs, cmd[0].args);
	if (!return_code)
		return_code = exec_sysfunction(cmd[0].command, cmd[0].args);
	return (return_code);
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

void	msh_loop(char **builtin_funcs)
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
		status = msh_execute(cmd, builtin_funcs);
		free(line);
		//free(args);
	}
}

int	main(void)
{
	char	*builtin_funcs[BUILTIN_FUNCS_NB];

	set_builtin_funcs(builtin_funcs);
	msh_loop(builtin_funcs);
}
