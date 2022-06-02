/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 00:33:02 by lprates           #+#    #+#             */
/*   Updated: 2022/06/02 01:51:14 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*if_env_unquote(char *str, char *s1, int *i)
{
	char	*env;
	char	*join;

	env = string_env(str, s1, i);
	if (env == NULL)
		return (free_str_ret_null(s1));
	if (s1 == NULL)
	{
		join = malloc(sizeof(char));
		join[0] = '\0';
	}
	join = ft_strjoin(s1, env);
	free_both(s1, env);
	return (join);
}

static char	*if_no_env_unquote(char *str, int *i, char *s1)
{
	char	*new;
	char	*join;
	int		start;

	start = *i;
	while (str[(*i)] && str[(*i)] != '\'' && str[(*i)] != '"'
		&& str[(*i)] != '$')
		(*i)++;
	new = malloc(sizeof(char) * ((*i) - start + 1));
	if (new == NULL)
		return (free_str_ret_null(s1));
	new = ft_strncpy(new, str + start, ((*i) - start));
	join = ft_strjoin(s1, new);
	free_both(s1, new);
	return (join);
}

char	*word_will_unquote(char *str, int *cur, char *s1)
{
	while (str[*cur] && str[*cur] != '\'' && str[*cur] != '"')
	{
		if (str[*cur] != '$')
		{
			s1 = if_no_env_unquote(str, cur, s1);
			if (s1 == NULL)
				return (NULL);
		}
		else if (str[*cur] && str[*cur] == '$')
		{
			s1 = if_env_unquote(str, s1, cur);
			if (s1 == NULL)
			{
				return (NULL);
			}
		}
	}
	return (s1);
}
