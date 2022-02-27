/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 08:41:47 by lprates           #+#    #+#             */
/*   Updated: 2022/02/26 21:39:07 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*move_to_delim(char *s, char delim, char *from)
{
	from = (char *)++s;
	from++;
	while (*s && *s != delim)
		++s;
	if (*s == 0 && delim != ' ')
		return (NULL);
	return (s);
}

static long long	w_cnt(char *s)
{
	long long	cnt;

	cnt = 0;
	while (*s)
	{
		if (*s != ' ')
		{
			cnt++;
			if (*s == '"')
				s = move_to_delim((char *)s, '"', s);
			else if (*s == '\'')
				s = move_to_delim((char *)s, '\'', s);
			else
				s = move_to_delim((char *)s, ' ', s);
		}
		if (*s != 0)
			s++;
	}
	return (cnt);
}

static void	loc_strcpy(char *dst, char *from, char *until)
{
	while (from < until)
		*(dst++) = *(from++);
	*dst = 0;
}

char	**local_split(char const *s, char *delim)
{
	char		**ret;
	long long	idx;
	char		*from;

	ret = (char **)malloc(sizeof(char *) * w_cnt((char *)s) + 1);
	if (!s || !ret)
		return (NULL);
	idx = 0;
	while (*s)
	{
		if (*s != ' ')
		{
			from = (char *)s;
			if (ft_strchr(delim, *s))
				s = move_to_delim((char *)s, *s, ++from);
			else
				s = move_to_delim((char *)s, ' ', from);
			ret[idx] = (char *)malloc(s - from + 1);
			loc_strcpy(ret[idx++], from, (char *)s);
		}
		if (*s != 0)
			++s;
	}
	ret[idx] = 0;
	return (ret);
}
