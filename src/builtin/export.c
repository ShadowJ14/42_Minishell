/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:27:03 by rramos            #+#    #+#             */
/*   Updated: 2022/03/26 17:42:59 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_args(char **args)
{
	(void)args;
}

static void	print_export(t_environment_element *environment_linked_list)
{
	t_environment_element	*environment_element;

	environment_element = environment_linked_list;
	while (environment_element != NULL)
	{
		printf("%s=%s\n", environment_element->name, environment_element->value);
		environment_element = environment_element->next_element;
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
void	do_export(char **args, t_environment_element **environment_linked_list)
{
	if (args[1] == NULL)
	{
		print_export(*environment_linked_list);
		return ;
	}
	verify_args(args);
	set_args(args);
}
