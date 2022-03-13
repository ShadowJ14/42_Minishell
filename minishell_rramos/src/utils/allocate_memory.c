/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 18:03:09 by rramos            #+#    #+#             */
/*   Updated: 2022/03/13 20:08:56 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*realloc_n_initialize_cmd(t_command *cmd, int idx)
{
	int	tmp;

	tmp = sizeof(t_command);
	if (idx == 0)
		cmd = malloc(sizeof(t_command));
	else
		cmd = ft_realloc(cmd, tmp * (idx + 1), tmp * (idx + 2));
	if (!cmd)
		return (NULL);
	ft_memset(&cmd[idx], 0, sizeof(t_command));
	return (cmd);
}

void	*allocate_memory(size_t size)
{
	void	*memory_pointer;

	memory_pointer = malloc(size);
	return (memory_pointer);
}
