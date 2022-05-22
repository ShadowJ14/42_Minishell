/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 22:38:13 by lprates           #+#    #+#             */
/*   Updated: 2022/05/22 22:44:27 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void	update_shlvl(void)
{
	t_env_elem	*new_env_llist;
	int			old_value;

	new_env_llist = singleton(NULL);
	while (new_env_llist->next_element != NULL)
	{
		if (!ft_strcmp(new_env_llist->name, "SHLVL"))
		{
			old_value = ft_atoi(new_env_llist->value);
			old_value++;
			new_env_llist->value = ft_itoa(old_value);
		}
		new_env_llist = new_env_llist->next_element;
	}
}
