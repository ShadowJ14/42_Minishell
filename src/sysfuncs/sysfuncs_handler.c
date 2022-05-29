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

char	*check_sysfunction(char *func)
{
	char	*envs;
	char	**ret;
	char	*cmd;

	envs = getenv("PATH");
	ret = ft_split(envs, ':');
	while (*ret)
	{
		cmd = ft_strjoin(*ret, ft_strjoin("/", func));
		if (access(cmd, X_OK) == 0)
			return (cmd);
		if (access(func, X_OK) == 0)
			return (func);
		free(cmd);
		if (*ret)
			ret++;
	}
	return (NULL);
}

/*
** funtions that handles the redirection in and append in to file
**
*/
