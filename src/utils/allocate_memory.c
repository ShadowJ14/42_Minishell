/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 18:03:09 by rramos            #+#    #+#             */
/*   Updated: 2022/03/16 01:36:46 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*realloc_n_initialize_cmd(t_command *cmd, int idx)
{
	int	cmd_size;

	cmd_size = sizeof(t_command);
	if (idx == 0)
		cmd = malloc(cmd_size * 2);
	else
		cmd = ft_realloc(cmd, cmd_size * (idx + 2), cmd_size * (idx + 3));
	if (!cmd)
		return (NULL);
	ft_memset(&cmd[idx], 0, cmd_size * 2);
	return (cmd);
}
	//ft_memset(&cmd[idx + 1], 0, sizeof(t_command));

void	*allocate_memory(size_t size)
{
	void	*memory_pointer;

	memory_pointer = malloc(size);
	return (memory_pointer);
}
