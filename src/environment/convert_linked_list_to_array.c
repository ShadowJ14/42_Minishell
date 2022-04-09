/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_linked_list_to_array.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:35:56 by rramos            #+#    #+#             */
/*   Updated: 2022/04/04 19:03:07 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	calculate_linked_list_length(t_environment_element *environment_element)
{
	size_t	length;

	length = 0;
	if (environment_element != NULL)
	{
		length++;
		while (environment_element->next_element != NULL)
		{
			length++;
			environment_element = environment_element->next_element;
		}
	}
	return (length);
}

char **convert_linked_list_to_array(t_environment_element *environment_element)
{
	char	**environment_array;
	size_t	index;
	size_t	length;

	length = calculate_linked_list_length(environment_element);
	environment_array = allocate_memory(sizeof(*environment_array) * \
		(length + 1));
	index = 0;
	while (index < length)
	{
		environment_array[index] = ft_strjoin(ft_strjoin(environment_element->name, "="), environment_element->value);
		index++;
		environment_element = environment_element->next_element;
	}
	environment_array[index] = NULL;
	return (environment_array);
}
