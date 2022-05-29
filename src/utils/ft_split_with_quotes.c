/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 08:41:47 by lprates           #+#    #+#             */
/*   Updated: 2022/05/22 23:18:16 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	loc_strcpy(char *dst, char *from, char *until)
{
	while (from < until)
		*(dst++) = *(from++);
	*dst = 0;
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
			else if (*s == '<' || *s == '>')
				s = move_to_end_redirect((char *)s, *s, NULL);
			else
				s = move_to_delim((char *)s, ' ', s);
		}
		if (*s != 0)
			s++;
	}
	return (cnt);
}

static char	*move_it(char *s, char *from)
{
	if (*s == '"')
		s = move_to_delim((char *)s, '"', from);
	else if (*s == '\'')
		s = move_to_delim((char *)s, '\'', from);
	else if (*s == '<' || *s == '>')
		s = move_to_end_redirect((char *)s, *s, from);
	else
		s = move_to_delim((char *)s, ' ', from);
	return (s);
}

static char	*set_filename(t_cmd *cmd, char *from, char *s)
{
	while (*s && ft_isblank(*s))
		if (*s != 0 && !ft_strchr("><", *s))
			s++;
	from = s;
	s = move_it((char *)s, from);
	if (ft_strstr(from, "\"\""))
	{
		cmd->file = (char *)malloc(s - 2 - from + 1);
		loc_strcpy(cmd->file, from, (char *)s - 2);
		cmd->no_expand = 1;
	}
	else
	{
		cmd->file = (char *)malloc(s - from + 1);
		loc_strcpy(cmd->file, from, (char *)s);
		cmd->no_expand = 0;
	}
	return (s);
}

char	**smart_split(char const *s, t_cmd *cmd)
{
	char		**ret;
	long long	idx;
	char		*from;

	ret = (char **)malloc(sizeof(char *) * (w_cnt((char *)s) + 1));
	if (!s || !ret)
		return (NULL);
	idx = 0;
	while (*s)
	{
		if (!ft_isblank(*s))
		{
			from = (char *)s;
			s = move_it((char *)s, from);
			if (*from == '<' || *from == '>')
				s = set_filename(cmd, from, (char *)s);
			else
				set_args(ret, s, from, idx++);
		}
		if (*s != 0 && !ft_strchr("><", *s))
			++s;
	}
	ret[idx] = NULL;
	return (ret);
}
