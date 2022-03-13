/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 08:41:47 by lprates           #+#    #+#             */
/*   Updated: 2022/03/13 22:19:54 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static char	*move_to_delim(char *s, char delim, char *from)
{
	from = (char *)++s;
	from++;
	while (*s && *s != delim)
		++s;
	return (s);
}

static long long	w_cnt(char *s, char *delim)
{
	long long	cnt;

	cnt = 0;
	while (*s)
	{
		if (!ft_strchr(delim, *s))
		{
			cnt++;
			while (!ft_strchr(delim, *s))
				s++;
			if ((*s == '>' && *(s + 1) == '>')
				|| (*s == '<' && *(s + 1) == '<'))
				s++;
		}
		if (*s != 0)
			s++;
	}
	printf("cnt %lli\n", cnt);
	return (cnt);
}*/

int	set_chain(char delim, char append)
{
	if (delim == '>')
	{
		if (delim == append)
			return (APPENDO);
		else
			return (REDIRECTO);
	}
	if (delim == '<')
	{
		if (delim == append)
			return (APPENDI);
		else
			return (REDIRECTI);
	}
	if (delim == '|')
		return (PIPE);
	return (0);
}

static t_command	*realloc_n_initialize_cmd(t_command *cmd, int idx)
{
	int	tmp;

	tmp = sizeof(t_command);
	if (idx == 0)
		cmd = malloc(sizeof(t_command));
	else
		cmd = ft_realloc(cmd, tmp * (idx + 1), tmp * (idx + 2));
	if (!cmd)
		return (NULL);
	ft_memset(&cmd[idx], 0, sizeof(t_command));
	return (cmd);
}

static void	loc_strcpy(char *dst, char *from, char *until)
{
	while (from < until)
		*(dst++) = *(from++);
	*dst = 0;
}

t_command	handle_cmd(char *ret, char delim, char append)
{
	char		*from;
	char		*tmp;
	t_command	cmd;

	from = ret;
	while (!ft_strchr(" ", *ret) && *ret)
		ret++;
	cmd.command = (char *)malloc(ret - from + 1);
	loc_strcpy(cmd.command, from, (char *)ret);
	while (ft_isblank(*ret))
		ret++;
	//from = ret;
	while (*ret)
		ret++;
	while (ft_isblank(*(ret - 1)))
		ret--;
	tmp = (char *)malloc(ret - from + 1);
	loc_strcpy(tmp, from, (char *)ret);
	cmd.args = malloc(sizeof(char *) + 1);
	cmd.args = ft_split(tmp, ' ');
	cmd.chain = set_chain(delim, append);
	return (cmd);
}

int	ops(char const *s, char *delim, t_command *cmd, int idx)
{
	char		*from;
	char		*ret;

	from = (char *)s;
	while (!ft_strchr(delim, *s) && *s)
		s++;
	ret = (char *)malloc(s - from + 1);
	if (!ret || !cmd)
		return (-1);
	loc_strcpy(ret, from, (char *)s);
	if (ft_strchr(delim, *s) && *s)
	{
		cmd[idx++] = handle_cmd(ret, *s, *(s + 1));
		cmd = realloc_n_initialize_cmd(cmd, idx);
	}
	else
		cmd[idx] = handle_cmd(ret, 0, 0);
	while (ft_strchr(delim, *s) && *s)
		s++;
	return (s - from);
}

t_command	*local_split(char const *s, char *delim)
{
	t_command	*cmd;
	int			idx;

	idx = 0;
	cmd = NULL;
	cmd = realloc_n_initialize_cmd(cmd, 0);
	if (!s || !cmd)
		return (NULL);
	while (*s)
	{
		while (ft_isblank(*s))
			s++;
		if (!ft_strchr(delim, *s))
		{
			s += ops(s, delim, cmd, idx);
			idx++;
		}
	}
	return (cmd);
}
