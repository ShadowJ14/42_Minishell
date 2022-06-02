/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 23:39:00 by lprates           #+#    #+#             */
/*   Updated: 2022/06/01 23:42:43 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd_all(t_cmd **cmd)
{
	t_cmd	*cur;

	cur = *cmd;
	while (cur->exec)
	{
		if (cur->pipe[0] != 0)
			close(cur->pipe[0]);
		if (cur->pipe[1] != 1)
			close(cur->pipe[1]);
		cur++;
	}
}

int	open_fd(t_cmd *cmd)
{
	t_cmd	*cur;

	cur = cmd;
	if (cur->chain == REDIRECTI || cur->chain == HEREDOC)
		if (redirect_file_in(cur, cur->chain) == -1)
			return (-1);
	if (cur->chain == REDIRECTO || cur->chain == APPEND)
		if (redirect_file_out(cur, cur->chain) == -1)
			return (-1);
	return (0);
}
