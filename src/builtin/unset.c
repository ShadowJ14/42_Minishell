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
	t_env_elem	*env_elem_freed;
	t_env_elem	**tmp;

	tmp = env_linklist;
	while (*args != NULL)
	{
		if (*env_linklist != NULL && !ft_strcmp((*env_linklist)->name, *args))
		{
			*env_linklist = (*env_linklist)->next_element;
			free_both((*env_linklist)->name, (*env_linklist)->value);
			free_memory((void **)env_linklist);
			args++;
			continue ;
		}
		while (*env_linklist != NULL)
		{
			if (!ft_strcmp((*env_linklist)->name, *args))
			{
				env_elem_freed = *env_linklist;
				*env_linklist = (*env_linklist)->next_element;
				free_both(env_elem_freed->name, env_elem_freed->value);
				free_memory((void **)&env_elem_freed);
				break ;
			}
			else
				env_linklist = &(*env_linklist)->next_element;
		}
		env_linklist = tmp;
		args++;
	}
}

// implements unset builtin
void	do_unset(char **args)
{
	t_env_elem	*env_linklist;

	env_linklist = env_singleton(NULL);
	if (args[1] == NULL)
	{
		print_error_message("unset: not enough arguments\n");
		return ;
	}
	unset_args(args, &env_linklist);
}
