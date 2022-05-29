/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_quotes_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 19:02:16 by lprates           #+#    #+#             */
/*   Updated: 2022/05/29 19:06:09 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	loc_strcpy(char *dst, char *from, char *until)
{
	while (from < until)
		*(dst++) = *(from++);
	*dst = 0;
}

char	*move_to_delim(char *s, char delim, char *from)
{
	from = (char *)s;
	(void) from;
	s++;
	if (delim == ' ' || delim == '\"' || delim == '\'')
		while (*s && *s != delim)
			++s;
	else
		while (*s && *s != delim && !ft_strchr("><", *s))
			++s;
	if (*s == 0 && delim != ' ')
		return (NULL);
	if (*s == '\"' || *s == '\'')
		s++;
	return (s);
}

char	*move_to_end_redirect(char *s, char delim, char *from)
{
	from = (char *)s;
	(void) from;
	while (*s && *s == delim)
		++s;
	return (s);
}

void	set_args(char **ret, char const *s, char *from, int idx)
{
	ret[idx] = (char *)malloc(s - from + 1);
	loc_strcpy(ret[idx], from, (char *)s);
}
