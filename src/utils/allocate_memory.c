/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_mem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 18:03:09 by rramos            #+#    #+#             */
/*   Updated: 2022/05/22 23:33:00 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*realloc_n_initialize_cmd(t_cmd *cmd, int idx)
{
	int	cmd_size;

	cmd_size = sizeof(t_cmd);
	if (idx == 0)
		cmd = malloc(cmd_size * 2);
	else
		cmd = ft_realloc(cmd, cmd_size * (idx + 1), cmd_size * (idx + 2));
	if (!cmd)
		return (NULL);
	ft_memset(&cmd[idx], 0, cmd_size * 2);
	cmd[idx].exec = 0;
	return (cmd);
}
	//ft_memset(&cmd[idx + 1], 0, sizeof(t_cmd));

void	*alloc_mem(size_t size)
{
	void	*memory_pointer;

	if (size == 0)
		return (NULL);
	memory_pointer = malloc(size);
	if (memory_pointer == NULL)
		print_error_message("Failed to allocate memory.\n");
	return (memory_pointer);
}
