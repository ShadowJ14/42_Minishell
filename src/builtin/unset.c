/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:27:58 by rramos            #+#    #+#             */
/*   Updated: 2022/03/26 17:50:08 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_args(char **args, t_environment_element **environment_linked_list)
{
	t_environment_element	*environment_element;
	t_environment_element	*environment_element_unsetted;
	size_t					index;

	index = 1;
	while (args[index] != NULL)
	{
		environment_element = *environment_linked_list;
		if (!ft_strcmp(environment_element->name, args[index]))
		{
			printf("Log 1.\n");
			*environment_linked_list = (*environment_linked_list)->next_element;
			free(environment_element);
			index++;
			continue ;
		}
		while (environment_element != NULL)
		{
			if (!ft_strcmp(environment_element->name, args[index]))
			{
				printf("Log 2.\n");
				environment_element_unsetted = environment_element;
				free(environment_element_unsetted);
				break ;
			}
			environment_element = environment_element->next_element;
		}
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
