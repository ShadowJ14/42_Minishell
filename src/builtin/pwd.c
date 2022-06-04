/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 20:50:50 by lprates           #+#    #+#             */
/*   Updated: 2022/05/20 23:27:09 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_built_in_pwd_fd(int fd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		g_exit_code = errno;
		return (EXIT_FAILURE);
	}
	g_exit_code = 0;
	ft_putstr_fd(pwd, fd);
	ft_putchar_fd('\n', fd);
	free(pwd);
	return (0);
}
