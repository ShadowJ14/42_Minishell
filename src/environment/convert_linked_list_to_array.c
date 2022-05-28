/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_linked_list_to_array.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:35:56 by rramos            #+#    #+#             */
/*   Updated: 2022/05/22 18:55:04 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	calculate_linked_list_length(t_env_elem *env_elem)
{
	size_t	length;

	length = 0;
	if (env_elem != NULL)
	{
		length++;
		while (env_elem->next_element != NULL)
		{
			length++;
			env_elem = env_elem->next_element;
		}
	}
	return (length);
}

static char	*free_join(char *join, char *new)
{
	char	*ret;

	ret = ft_strjoin(join, new);
	free(join);
	return (ret);
}

char	**convert_linked_list_to_array(t_env_elem *env_elem)
{
	char	**environment_array;
	size_t	index;
	size_t	length;

	length = calculate_linked_list_length(env_elem);
	environment_array = allocate_memory(sizeof(*environment_array) * \
		(length + 1));
	index = 0;
	while (index < length)
	{
		environment_array[index] = free_join(ft_strjoin(env_elem->name, "="), \
			env_elem->value);
		index++;
		env_elem = env_elem->next_element;
	}
	environment_array[index] = NULL;
	return (environment_array);
}
