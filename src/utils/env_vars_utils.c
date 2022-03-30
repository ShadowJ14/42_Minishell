/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:48:49 by lprates           #+#    #+#             */
/*   Updated: 2022/03/30 01:49:18 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Expands env variables allocating memory for the return value
*/
char	*expand_env_var(t_environment_element *environment_linked_list, \
						char *env_name)
{
	char	*expanded_name;
	int		expanded_size;

	while (environment_linked_list != NULL)
	{
		if (!ft_strcmp(environment_linked_list->name, env_name))
		{
			expanded_size = ft_strlen(environment_linked_list->value);
			expanded_name = malloc(sizeof(char) * expanded_size);
			ft_strlcpy(expanded_name, environment_linked_list->value, \
				expanded_size + 1);
			return (expanded_name);
		}
		environment_linked_list = environment_linked_list->next_element;
	}
	return (NULL);
}
