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

static int	nextlink_free(t_env_elem **env_linklist)
{
	*env_linklist = (*env_linklist)->next_element;
	free_both((*env_linklist)->name, (*env_linklist)->value);
	free_memory((void **)env_linklist);
	return (1);
}

static int	env_elem_free(t_env_elem **env_linklist, t_env_elem *env_elem_freed)
{
	*env_linklist = (*env_linklist)->next_element;
	free_both(env_elem_freed->name, env_elem_freed->value);
	free_memory((void **)&env_elem_freed);
	return (1);
}

static void	unset_args(char **args, t_env_elem **env_linklist)
{
	t_env_elem	*env_elem_freed;
	t_env_elem	**tmp;

	env_elem_freed = NULL;
	tmp = env_linklist;
	while (*args != NULL)
	{
		if (*env_linklist != NULL && !ft_strcmp((*env_linklist)->name, *args))
			if (nextlink_free(env_linklist) && args++)
				continue ;
		while (*env_linklist != NULL)
		{
			if (!ft_strcmp((*env_linklist)->name, *args))
			{
				env_elem_freed = *env_linklist;
				env_elem_free(env_linklist, env_elem_freed);
				break ;
			}
			else
				env_linklist = &(*env_linklist)->next_element;
		}
		env_linklist = tmp;
		args++;
	}
}

void	do_unset(char **args)
{
	t_env_elem	*env_linklist;

	env_linklist = env_singleton(NULL);
	if (args[1] == NULL)
	{
		g_exit_code = 0;
		return ;
	}
	unset_args(args, &env_linklist);
}
