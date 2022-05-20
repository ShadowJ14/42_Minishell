/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 21:19:46 by lprates           #+#    #+#             */
/*   Updated: 2022/05/20 21:26:43 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	free_all(t_cmd **cmd)
{
	int		i;

	i = -1;
	if (cmd)
	{
		while (cmd[++i]->exec)
		{
			if (cmd[i]->exec)
				free((*cmd)->exec);
			if (cmd[i]->args)
				free(cmd[i]->args);
			if (cmd[i]->file)
				free(cmd[i]->file);
			free(cmd[i]);
		}
	}
	return (1);
}
