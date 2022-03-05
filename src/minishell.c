/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 04:07:52 by lprates           #+#    #+#             */
/*   Updated: 2022/03/05 14:51:32 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_execute(char **args, char **builtin_funcs)
{
	int	return_code;

	return_code = builtin(args[0], builtin_funcs, args);
	if (!return_code)
		return_code = exec_sysfunction(args);
	return (return_code);
}

char	**msh_split_line(char *line)
{
	char	**args;

	args = local_split(line, "\'\"");
	if (!args)
		return (NULL);
	return (args);
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
	char	*line;
	char	**args;
	int		status;

	status = 1;
	while (status)
	{
		line = msh_readline();
		args = msh_split_line(line);
		if (!args)
		{
			printf("Erro caralho!\n");
			return ;
		}
		// while (*args)
		// {
		// 	printf("arg: %s\n", *args);
		// 	args++;
		// }
		status = msh_execute(args, builtin_funcs);
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
