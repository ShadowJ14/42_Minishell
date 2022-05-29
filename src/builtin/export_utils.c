/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 15:28:25 by lprates           #+#    #+#             */
/*   Updated: 2022/05/29 16:13:58 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(void)
{
	t_env_elem	*env_linklist;

	env_linklist = env_singleton(NULL);
	while (env_linklist != NULL)
	{
		print_message(env_linklist->name);
		print_message("=");
		if (env_linklist->value[0] == '\0')
			print_message("");
		else
			print_message(env_linklist->value);
		print_message("\n");
		env_linklist = env_linklist->next_element;
	}
}
