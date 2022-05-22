/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:27:58 by rramos            #+#    #+#             */
/*   Updated: 2022/05/22 18:50:31 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_args(char **args, t_env_elem **env_linklist)
{
	t_env_elem	**env_elem;
	t_env_elem	*env_elem_freed;
	size_t		index;

	index = 1;
	while (args[index] != NULL)
	{
		env_elem = env_linklist;
		if (!ft_strcmp((*env_elem)->name, args[index]))
		{
			*env_linklist = (*env_linklist)->next_element;
			free_memory((void **)env_elem);
			index++;
			continue ;
		}
		while (*env_elem != NULL)
		{
			if (!ft_strcmp((*env_elem)->name, args[index]))
			{
				env_elem_freed = *env_elem;
				*env_elem = (*env_elem)->next_element;
				free_memory((void **)&env_elem_freed);
				break ;
			}
			else
			{
				env_elem = &(*env_elem)->next_element;
			}
		}
		index++;
	}
}

// implements unset builtin
void	do_unset(char **args, t_env_elem **env_linklist)
{
	if (args[1] == NULL)
	{
		print_error_message("unset: not enough arguments\n");
		return ;
	}
	unset_args(args, env_linklist);
}
