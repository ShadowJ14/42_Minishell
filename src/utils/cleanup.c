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

int	free_array(void **str)
{
	while (*str)
	{
		free(*str);
		str++;
	}
	return (1);
}

void	free_env_llist(t_env_elem *env_llist)
{
	t_env_elem	*tmp;

	while (env_llist)
	{
		free(env_llist->name);
		free(env_llist->value);
		tmp = env_llist;
		env_llist = env_llist->next_element;
		free(tmp);
	}
}
