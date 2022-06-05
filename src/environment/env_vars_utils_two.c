/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_utils_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 00:42:51 by lprates           #+#    #+#             */
/*   Updated: 2022/06/04 16:57:34 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Expands env variables allocating memory for the return value
*/
char	*expand_env_var(char *env_name)
{
	char		*expanded_name;
	int			expanded_size;
	t_env_elem	*env_linklist;

	env_linklist = env_singleton(NULL);
	if (!env_name || !ft_strcmp(env_name, "$"))
		return ("$");
	while (env_linklist != NULL)
	{
		if (!ft_strcmp(env_linklist->name, env_name))
		{
			expanded_size = ft_strlen(env_linklist->value);
			if (!expanded_size)
				return (NULL);
			expanded_name = malloc(sizeof(char) * expanded_size + 1);
			if (expanded_name == NULL)
			{
				g_exit_code = errno;
				return (NULL);
			}
			ft_strlcpy(expanded_name, env_linklist->value, \
				expanded_size + 1);
			return (expanded_name);
		}
		env_linklist = env_linklist->next_element;
	}
	return (NULL);
}

t_quote	update_quote_succes(int *i, t_quote quote, char **s1)
{
	(*i)++;
	if (*s1 == NULL)
	{
		*s1 = malloc(sizeof(char));
		if (*s1 != NULL)
			(*s1)[0] = '\0';
	}
	return (quote);
}

t_quote	update_quote_status(char c, t_quote quote)
{
	if (c == '"')
	{
		if (quote == NONE)
			return (DOUBLE);
		else if (quote == DOUBLE)
			return (NONE);
	}
	else if (c == '\'')
	{
		if (quote == NONE)
			return (SINGLE);
		else if (quote == SINGLE)
			return (NONE);
	}
	return (quote);
}
