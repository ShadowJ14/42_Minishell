/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_split_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 01:44:42 by lprates           #+#    #+#             */
/*   Updated: 2022/03/12 03:24:39 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*realloc_n_initialize_cmd(t_command *cmd, int idx)
{
	int	tmp;

	tmp = sizeof(t_command);
	if (idx == 0)
		cmd = malloc(sizeof(t_command));
	else
		cmd = ft_realloc(cmd, tmp * (idx + 1), tmp * (idx + 2));
	if (!cmd)
		return (NULL);
	cmd[idx].args = 0;
	cmd[idx].chain = 0;
	cmd[idx].command = 0;
	return (cmd);
}

t_command	*get_commands(char *line)
{
	t_command	*cmd;
	char		**ret;
	int			idx;
	int			first;

	idx = 0;
	first = 1;
	cmd = NULL;
	cmd = realloc_n_initialize_cmd(cmd, idx);
	if (!cmd)
		return (NULL);
	ret = ft_split(line, ' ');
	while (*ret)
	{
		if (first)
		{
			cmd[idx].command = ft_strdup(*ret);
			ret++;
			first = 0;
		}
		if (*ret)
		{
			if (ft_strchr(*ret, '|'))
			{
				cmd[idx].chain = PIPE;
				first = 1;
				idx++;
				cmd = realloc_n_initialize_cmd(cmd, idx);
			}
			else
			{
				if (cmd[idx].args == NULL)
					cmd[idx].args = ft_strdup(*ret);
				else
				{
					cmd[idx].args = ft_strjoin(cmd[idx].args, " ");
					cmd[idx].args = ft_strjoin(cmd[idx].args, *ret);
				}
			}
			ret++;
		}
	}
	printf("command1: %s args: %s sep: %i\n", cmd[0].command, cmd[0].args, cmd[0].chain);
	printf("command2: %s sep: %i\n", cmd[1].command, cmd[1].chain);
	return (cmd);
}
