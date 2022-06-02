/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:48:49 by lprates           #+#    #+#             */
/*   Updated: 2022/05/22 19:01:31 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

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

char	*get_envp(char *str, int *cur)
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
	ft_strncpy(cpy, str + 1, len_str);
	env = expand_env_var(cpy);
	free(cpy);
	if (env == NULL)
		return (fake_env(cur, len_str));
	*cur = *cur + len_str + 1;
	cpy = ft_strdup(env);
	return (cpy);
}

char	*get_env(int *cur, char *str)
{
	char	*s3;

	s3 = get_envp(str + *cur, cur);
	return (s3);
}
