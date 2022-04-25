/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:48:49 by lprates           #+#    #+#             */
/*   Updated: 2022/04/25 05:42:09 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

static char	*if_env_two(char *str, char *s1, int *i, t_env_elem *env_linklist)
{
	char	*env;

	env = string_env(str, s1, i, env_linklist);
	if (env == NULL)
		return (NULL);
	free(s1);
	return (env);
}

static char	*if_no_env_two(char *str, int *i, char *s1)
{
	char	*new;
	int		start;

	start = *i;
	(void)s1;
	while (str[(*i)] && str[(*i)] != '\'' && str[(*i)] != '"'
		&& str[(*i)] != '$')
		(*i)++;
	new = malloc(sizeof(char) * ((*i) - start + 1));
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, str + start, ((*i) - start) + 1);
	//join = ft_strjoin(s1, new);
	//free_both(s1, new);
	return (new);
}

char	*word_will_unquote(char *str, int *cur, char *s1, t_env_elem *env_linklist)
{
	while (str[*cur] && str[*cur] != '\'' && str[*cur] != '"')
	{
		if (str[*cur] != '$')
		{
			s1 = if_no_env_two(str, cur, s1);
			if (s1 == NULL)
				return (NULL);
		}
		else if (str[*cur] && str[*cur] == '$')
		{
			s1 = if_env_two(str, s1, cur, env_linklist);
			if (s1 == NULL)
			{
				return (NULL);
			}
		}
	}
	return (s1);
}

int	ft_is_alpha_num(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (0);
	return (1);
}

int	get_len_env_var(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '$')
		str++;
	if (str[0] && str[0] == '?')
		return (1);
	while (str[i] && (ft_is_alpha_num(str[i]) == 0 || str[i] == '_'))
		i++;
	return (i);
}

int	is_env(char *str, char *env, int len)
{
	int	i;

	i = 0;
	while (str[i] && i < len)
	{
		if (str[i] == '\0' || env[i] == '\0')
			return (-1);
		if (str[i] != env[i])
			return (-1);
		i++;
	}
	if (env[i] && env[i] == '=')
		return (0);
	return (-1);
}

char	*alloc_dollar(int *cur)
{
	char	*new;

	*cur = *cur + 1;
	new = malloc(sizeof(char) * 2);
	if (new)
	{
		new[0] = '$';
		new[1] = '\0';
		return (new);
	}
	return (NULL);
}

char	*fake_env(int *j, int len_str)
{
	char	*new;

	new = NULL;
	*j = *j + len_str + 1;
	new = malloc(sizeof(char));
	if (new == NULL)
		return (NULL);
	new[0] = '\0';
	return (new);
}

char	*get_envp(char *str, int *cur, t_env_elem *env_linklist)
{
	int		len_str;
	char	*cpy;
	char	*env;

	cpy = NULL;
	len_str = get_len_env_var(str);
	if (len_str == 0)
		return (alloc_dollar(cur));
	if (len_str == 1 && str[1] == '?')
	{
		*cur = *cur + 2;
		return (ft_itoa(g_exit_code));
	}
	cpy = malloc(sizeof(char) * (len_str + 1));
	if (cpy == NULL)
		return (NULL);
	ft_strlcpy(cpy, str + 1, len_str + 1);
	env = expand_env_var(env_linklist, cpy);
	free(cpy);
	if (env == NULL)
		return (fake_env(cur, len_str));
	*cur = *cur + len_str + 1;
	cpy = ft_strdup(env);
	return (cpy);
}

char	*get_env(int *cur, char *str, t_env_elem *env_linklist)
{
	char	*s3;

	s3 = get_envp(str + *cur, cur, env_linklist);
	return (s3);
}

/*
** Expands env variables allocating memory for the return value
*/
char	*expand_env_var(t_env_elem *env_linklist, \
						char *env_name)
{
	char	*expanded_name;
	int		expanded_size;

	if (!env_name || !ft_strcmp(env_name, "$"))
		return ("$");
	while (env_linklist != NULL)
	{
		if (!ft_strcmp(env_linklist->name, env_name))
		{
			expanded_size = ft_strlen(env_linklist->value);
			expanded_name = malloc(sizeof(char) * expanded_size);
			ft_strlcpy(expanded_name, env_linklist->value, \
				expanded_size + 1);
			return (expanded_name);
		}
		env_linklist = env_linklist->next_element;
	}
	return ("");
}

char	*expand_env_var_string(t_env_elem *env_linklist, \
			char *str, char *first)
{
	int		idx;
	char	*from;
	char	*to;
	char	*tmp;
	char	*s1;

	idx = 0;
	from = str;
	tmp = NULL;
	to = NULL;
	(void) first;
	while (str[idx])
	{
		tmp = ft_strchr(&str[idx], '$');
		if (tmp)
		{
			to = tmp - 1;
			idx = tmp - from;
			while (!ft_isblank(*(tmp + 1)) && *(tmp + 1))
			{
				idx++;
				tmp++;
			}
			tmp = malloc(sizeof(char) * (to - from) + 2);
			if (!tmp)
				return (NULL);
			ft_strlcpy(tmp, from, to + 2 - from);
			tmp = ft_strjoin(tmp, expand_env_var(env_linklist, to + 2));
			s1 = malloc(ft_strlen(tmp) + to + 2 - from);
			if (!s1)
				return (NULL);
			s1 = ft_strjoin(s1, tmp);
			from = &str[idx];
		}
		idx++;
	}
	return (s1);
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

static char	*if_no_env(char *str, char *s1, int *cur)
{
	char	*new;
	char	*join;
	int		start;

	start = *cur;
	while (str[*cur] && str[*cur] != '"' && str[*cur] != '$')
		(*cur)++;
	new = malloc(sizeof(char) * ((*cur) - start));
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, str + start, ((*cur) - start) + 1);
	join = ft_strjoin(s1, new);
	//free_both(s1, new);
	return (join);
}

char	*string_env(char *str, char *tmp, int *cur, t_env_elem *env_linklist)
{
	char	*tmp2;

	(void)tmp;
	tmp2 = NULL;
	tmp2 = get_env(cur, str, env_linklist);
	if (tmp2 == NULL)
		return (NULL);
	return (tmp2);
}

static char	*if_env(char *str, char *s1, int *cur, t_env_elem *env_linklist)
{
	char	*env;
	char	*join;

	env = string_env(str, s1, cur, env_linklist);
	if (env == NULL)
		return (NULL);
	join = ft_strjoin(s1, env);
	//free_both(s1, env);
	return (join);
}

char	*word_will_double(char *str, int *cur, char *s1, t_env_elem *env_linklist)
{
	while (str && str[*cur] && str[*cur] != '"')
	{
		if (str[*cur] == '$')
		{
			s1 = if_env(str, s1, cur, env_linklist);
			if (s1 == NULL)
				return (NULL);
		}
		else
		{
			s1 = if_no_env(str, s1, cur);
			if (s1 == NULL)
				return (NULL);
		}
	}
	return (s1);
}

char	*word_will_single(char *str, int *i, char *s1)
{
	char	*s2;
	char	*s3;
	int		j;

	s2 = NULL;
	s3 = NULL;
	j = *i;
	while (str && str[(*i)] && str[(*i)] != '\'')
		(*i)++;
	s2 = malloc(sizeof(char) * ((*i) - j + 1));
	if (s2 == NULL)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	ft_strlcpy(s2, str + j, (*i) - j + 1);
	s3 = ft_strjoin(s1, s2);
	//free_both(s1, s2);
	return (s3);
}

char	*init_str(char **str, char *duplica, int *cur, char **s1)
{
	*s1 = NULL;
	*cur = 0;
	*str = ft_strdup(duplica);
	free(duplica);
	if (*str == NULL)
		return (NULL);
	return (*str);
}

char	*word_modif_two(char *duplica, t_quote quote, t_quote prec, t_env_elem *env_linklist)
{
	char	*s1;
	int		cur;
	char	*str;

	if (init_str(&str, duplica, &cur, &s1) == NULL)
		return (NULL);
	while (str[cur])
	{
		quote = update_quote_status(str[cur], quote);
		if (prec != quote)
			prec = update_quote_succes(&cur, quote, &s1);
		else
		{
			if (quote == SINGLE)
				s1 = word_will_single(str, &cur, s1);
			else if (quote == DOUBLE)
				s1 = word_will_double(str, &cur, s1, env_linklist);
			else
				s1 = word_will_unquote(str, &cur, s1, env_linklist);
		}
		if (s1 == NULL)
			return (NULL);
	}
	return (s1);
}
