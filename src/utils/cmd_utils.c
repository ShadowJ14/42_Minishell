/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 01:13:59 by lprates           #+#    #+#             */
/*   Updated: 2022/05/21 01:14:11 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cmd_len(t_cmd *cur)
{
	int		count;
	t_cmd	*tmp;

	count = 0;
	tmp = cur;
	while (tmp->exec)
	{
		count++;
		tmp++;
	}
	return (count);
}
