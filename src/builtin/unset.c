/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:27:58 by rramos            #+#    #+#             */
/*   Updated: 2022/04/10 15:46:43 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	unset_argument(char **args, size_t index, \
	t_environment_element ***environment_element)
{
	t_environment_element	*environment_element_freed;

	if (!ft_strcmp((**environment_element)->name, args[index]))
	{
		environment_element_freed = **environment_element;
		**environment_element = (**environment_element)->next_element;
		free_memory((void **)&environment_element_freed);
		return (true);
	}
	else
		*environment_element = &(**environment_element)->next_element;
	return (false);
}

static void	unset_args(char **args, \
	t_environment_element **environment_linked_list)
{
	t_environment_element	**environment_element;
	size_t					index;

	index = 1;
	while (args[index] != NULL)
	{
		environment_element = environment_linked_list;
		if (!ft_strcmp((*environment_element)->name, args[index]))
		{
			*environment_linked_list = (*environment_linked_list)->next_element;
			free_memory((void **)environment_element);
			index++;
			continue ;
		}
		while (*environment_element != NULL)
			if (unset_argument(args, index, &environment_element))
				break ;
		index++;
	}
}

// implements unset builtin
void	do_unset(char **args, t_environment_element **environment_linked_list)
{
	if (args[1] == NULL)
	{
		print_error_message("unset: not enough arguments\n");
		return ;
	}
	unset_args(args, environment_linked_list);
}
