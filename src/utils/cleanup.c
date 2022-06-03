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

int	free_all(char *env)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	cmd = cmd_singleton(NULL);
	tmp = cmd;
	if (cmd)
	{
		while (cmd->exec)
		{
			if (cmd->args)
				free_array((void **)cmd->args);
			if (cmd->file)
				free(cmd->file);
			if (cmd->file_name)
				free(cmd->file_name);
			cmd++;
		}
	}
	free(tmp);
	if (env && !ft_strcmp(env, "ENV"))
		free_env_llist(env_singleton(NULL));
	return (1);
}

int	free_array(void **str)
{
	void	**tmp;

	tmp = str;
	while (*str)
	{
		free(*str);
		*str = NULL;
		str++;
	}
	free(tmp);
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
