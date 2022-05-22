/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 08:41:47 by lprates           #+#    #+#             */
/*   Updated: 2022/05/22 23:49:41 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_chain(char *tmp)
{
	char	*s;
	char	*s2;

	s = ft_strchr(tmp, '"');
	s2 = tmp;
	while (s != NULL)
	{
		s++;
		while (*s && *s != '\"')
			s++;
		if (*s == 0)
			break;
		s2 = s;
		s = ft_strchr(s, '\"');
	}
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

static void	loc_strcpy(char *dst, char *from, char *until)
{
	while (from < until)
		*(dst++) = *(from++);
	*dst = 0;
}

t_cmd	handle_cmd(char *ret)
{
	char	*from;
	char	*tmp;
	t_cmd	cmd;

	from = ret;
	while (!ft_strchr(" ", *ret) && *ret)
		ret++;
	//cmd.exec = (char *)malloc(ret - from + 1);
	//loc_strcpy(cmd.exec, from, (char *)ret);
	while (ft_isblank(*ret))
		ret++;
	while (*ret)
		ret++;
	while (ft_isblank(*(ret - 1)))
		ret--;
	tmp = (char *)malloc(ret - from + 1);
	loc_strcpy(tmp, from, (char *)ret);
	cmd.args = malloc(sizeof(char *) + 1);
	cmd.args = smart_split(tmp, " ", &cmd);
	cmd.chain = set_chain(tmp);
	free (tmp);
	return (cmd);
}

int	ops(char const *s, t_cmd *cmd, int idx)
{
	char		*from;
	char		*ret;
	char		quote;

	from = (char *)s;
	while ('|' != *s && *s)
	{
		if (ft_strchr("\"\'", *s))
		{
			quote = *s++;
			while (*s != quote)
				s++;
		}
		if (*s)
			s++;
	}
	ret = (char *)malloc(s - from + 1);
	if (!ret || !cmd)
		return (-1);
	loc_strcpy(ret, from, (char *)s);
	cmd[idx++] = handle_cmd(ret);
	free (ret);
	while ('|' != *s && *s)
		s++;
	return (s - from);
}

t_cmd	*local_split(char const *s)
{
	t_cmd	*cmd;
	int		idx;

	idx = 0;
	cmd = NULL;
	cmd = realloc_n_initialize_cmd(cmd, 0);
	if (!s || !cmd)
		return (NULL);
	while (*s)
	{
		while (ft_isblank(*s))
			s++;
		if (*s && '|' != *s)
		{
			s += ops(s, cmd, idx++);
			if (*s)
				cmd = realloc_n_initialize_cmd(cmd, idx);
		}
		else if (*s)
			s++;
	}
	return (cmd);
}
