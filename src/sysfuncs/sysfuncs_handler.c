/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sysfuncs_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:07:00 by lprates           #+#    #+#             */
/*   Updated: 2022/05/20 23:31:36 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*free_second(char *s1, char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (s2)
		free(s2);
	return (ret);
}

char	*check_sysfunction(char *func)
{
	char	*envs;
	char	**ret;
	char	*cmd;
	char	**tmp;

	if (access(func, X_OK) == 0)
		return (func);
	envs = expand_env_var("PATH");
	if (!envs)
		return (NULL);
	ret = ft_split(envs, ':');
	tmp = ret;
	while (*ret)
	{
		cmd = free_second(*ret, ft_strjoin("/", func));
		if (access(cmd, X_OK) == 0)
		{
			free_array((void **)tmp);
			free(envs);
			return (cmd);
		}
		free(cmd);
		if (*ret)
			ret++;
	}
	free(envs);
	free_array((void **)tmp);
	return (NULL);
}

/*
** funtions that handles the redirection in and append in to file
**
*/
