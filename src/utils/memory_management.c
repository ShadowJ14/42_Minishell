/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:19:14 by rramos            #+#    #+#             */
/*   Updated: 2022/05/22 21:33:14 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Memory management tracks memory pointers to easily free them to prevent memory leaks.
char	***singleton(bool initialize)
{
	static char **memory_management;

	if (initialize)
	{
		memory_management = malloc(sizeof(*memory_management) * 1);
		memory_management[0] = NULL;
		return (NULL);
	}
	return (&memory_management);
}

// Track a memory pointer.
void	track_memory(char ***memory_management, char *memory_to_track)
{
	size_t	index;
	size_t	length;
	char 	**new_memory_management;

	length = 0;
	while ((*memory_management)[length] != NULL)
		length++;
	new_memory_management = malloc(sizeof(*new_memory_management) * (length + 2));
	index = 0;
	while (index < length)
	{
		new_memory_management[index] = (*memory_management)[index];
		index++;
	}
	new_memory_management[index] = memory_to_track;
	new_memory_management[index + 1] = NULL;
	free(*memory_management);
	*memory_management = new_memory_management;
}

// Free a particular tracked memory pointer.
void	untrack_memory(char ***memory_management, char *memory_to_untrack)
{
	size_t	index_1;
	size_t	index_2;
	char 	**new_memory_management;

	if (memory_to_untrack == NULL)
		return ;
	index_1 = 0;
	index_2 = 0;
	while ((*memory_management)[index_1] != NULL)
	{
		if ((*memory_management)[index_1] != memory_to_untrack)
			index_2++;
		index_1++;
	}
	new_memory_management = malloc(sizeof(*new_memory_management) * (index_2 + 1));
	index_1 = 0;
	index_2 = 0;
	while ((*memory_management)[index_1] != NULL)
	{
		if ((*memory_management)[index_1] != memory_to_untrack)
		{
			new_memory_management[index_2] = (*memory_management)[index_1];
			index_2++;
		}
		index_1++;
	}
	new_memory_management[index_2] = NULL;
	free(*memory_management);
	*memory_management = new_memory_management;
}

// Free all the tracked memory pointers.
void	untrack_all_memory(char **memory_management)
{
	size_t	index;

	index = 0;
	while (memory_management[index] != NULL)
	{
		free(memory_management[index]);
		index++;
	}
	free(memory_management);
}

// Print all the tracked memory pointers (for debugging purposes).
void	print_all_tracked_memory(char **memory_management)
{
	size_t	index;

	print_message("Memory management: [");
	index = 0;
	while (memory_management[index] != NULL)
	{
		print_message(memory_management[index]);
		index++;
		if (memory_management[index] != NULL)
			print_message(", ");
	}
	print_message("].\n");
}
