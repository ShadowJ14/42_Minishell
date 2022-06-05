/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:48:27 by lprates           #+#    #+#             */
/*   Updated: 2022/06/05 16:59:41 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_quotes_two(char *s)
{
	char	*s2;

	s2 = NULL;
	while (s != NULL)
	{
		s++;
		while (*s && (*s != '\"' && *s != '\''))
			s++;
		if (*s == 0)
			break ;
		s2 = s;
		s = ft_strchr(s2, '\"');
		if (!s)
			s = ft_strchr(s2, '\'');
		if (s)
			s2 = s;
	}
	return (s2);
}

int	set_chain(char *tmp)
{
	char	*s;
	char	*s2;

	s = ft_strchr(tmp, '"');
	if (!s)
		s = ft_strchr(tmp, '\'');
	s2 = tmp;
	if (check_quotes_two(s))
		s2 = check_quotes_two(s);
	if (ft_strstr(s2, ">>"))
		return (APPEND);
	if (ft_strstr(s2, ">"))
		return (REDIRECTO);
	if (ft_strstr(s2, "<<"))
		return (HEREDOC);
	if (ft_strstr(s2, "<"))
		return (REDIRECTI);
	return (0);
}
