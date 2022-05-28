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

static int	set_filename(t_cmd *cmd, char *from, char const *s)
{
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
	return (0);
}

/*static int	set_file_chk(char from, int *file_chk)
{
	if (from == '<' || from == '>')
	{
		*file_chk = 1;
		return (1);
	}
	*file_chk = 0
	return (0);
}*/

static char	*move_to_delim(char *s, char delim, char *from)
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

static char	*move_to_end_redirect(char *s, char delim, char *from)
{
	from = (char *)s;
	(void) from;
	while (*s && *s == delim)
		++s;
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

static void	set_args_and_cmd(char **ret, char const *s, char *from, int idx, \
	t_cmd *cmd)
{
	ret[idx] = (char *)malloc(s - from + 1);
	loc_strcpy(ret[idx], from, (char *)s);
	if (idx == 0)
	{
		cmd->exec = (char *)malloc(s - from + 1);
		loc_strcpy(cmd->exec, from, (char *)s);
	}
}

char	**smart_split(char const *s, t_cmd *cmd)
{
	char		**ret;
	long long	idx;
	char		*from;
	int			file_chk;

	ret = (char **)malloc(sizeof(char *) * (w_cnt((char *)s) + 1));
	if (!s || !ret)
		return (NULL);
	idx = 0;
	file_chk = 0;
	while (*s)
	{
		if (*s != ' ')
		{
			from = (char *)s;
			s = move_it((char *)s, from);
			if (*from == '<' || *from == '>')
			{
				file_chk = 1;
				continue ;
			}
			if (file_chk)
				file_chk = set_filename(cmd, from, s);
			else
				set_args_and_cmd(ret, s, from, idx++, cmd);
		}
		if (*s != 0 && !ft_strchr("><", *s))
			++s;
	}
	ret[idx] = NULL;
	return (ret);
}
