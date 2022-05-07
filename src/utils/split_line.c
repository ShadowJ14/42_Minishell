/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:45:27 by lprates           #+#    #+#             */
/*   Updated: 2022/05/07 14:05:52 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*msh_split_line(char *line)
{
	t_cmd	*cmd;

	cmd = local_split(line);
	if (!cmd)
		return (NULL);
	return (cmd);
}
