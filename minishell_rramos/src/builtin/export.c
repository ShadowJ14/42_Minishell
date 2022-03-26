/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:27:03 by rramos            #+#    #+#             */
/*   Updated: 2022/03/26 11:55:29 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_args(char **args)
{
	(void)args;
}

static void	print_export(char **environ)
{
	size_t	index;

	index = 0;
	while (environ[index] != NULL)
	{
		printf("%s\n", environ[index]);
		index++;
	}
}

static void	verify_args(char **args)
{
	size_t	index;

	index = 1;
	while (args[index] != NULL)
	{
		if (!(ft_isalpha(args[index][0]) || args[index][0] == '_'))
			print_error_message(ft_strjoin(ft_strjoin("export: not an" \
				" identifier: ", args[index]), "\n"));
		index++;
	}
}

// implements export builtin
void	do_export(char **args, char **environ)
{
	if (args[1] == NULL)
	{
		print_export(environ);
		return ;
	}
	verify_args(args);
	set_args(args);
}
