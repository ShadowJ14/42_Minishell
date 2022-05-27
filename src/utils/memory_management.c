/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:19:14 by rramos            #+#    #+#             */
/*   Updated: 2022/05/22 22:46:26 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_elem	*env_singleton(t_env_elem *set_env_linklist)
{
	static t_env_elem	*env_linklist;

	if (set_env_linklist != NULL)
	{
		env_linklist = set_env_linklist;
		set_env_linklist = 0;
	}
	return (env_linklist);
}
