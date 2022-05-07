/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 08:41:47 by lprates           #+#    #+#             */
/*   Updated: 2022/05/07 19:51:49 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*move_to_delim(char *s, char delim, char *from)
{
	from = (char *)s;
	s++;
	while (*s && *s != delim)
		++s;
	if (*s == 0 && delim != ' ')
		return (NULL);
	if (*s == '\"' || *s == '\'')
		s++;
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

char	**smart_split(char const *s, char *delim, t_cmd *cmd)
{
	char		**ret;
	long long	idx;
	char		*from;
	int			file_chk;

	(void)delim;
	ret = (char **)malloc(sizeof(char *) * w_cnt((char *)s) + 1);
	if (!s || !ret)
		return (NULL);
	idx = 0;
	file_chk = 0;
	while (*s)
	{
		if (*s != ' ')
		{
			from = (char *)s;
			if (*s == '"')
				s = move_to_delim((char *)s, '"', from);
			else if (*s == '\'')
				s = move_to_delim((char *)s, '\'', from);
			else
				s = move_to_delim((char *)s, ' ', from);
			if (*from == '<' || *from == '>')
			{
				file_chk = 1;
				continue ;
			}
			if (file_chk)
			{
				cmd->file = (char *)malloc(s - from + 1);
				loc_strcpy(cmd->file, from, (char *)s);
				file_chk = 0;
			}
			else
			{
				ret[idx] = (char *)malloc(s - from + 1);
				loc_strcpy(ret[idx++], from, (char *)s);
			}
		}
		if (*s != 0)
			++s;
	}
	ret[idx] = 0;
	return (ret);
}
