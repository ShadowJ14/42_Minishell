/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 20:44:27 by lprates           #+#    #+#             */
/*   Updated: 2022/05/20 23:27:10 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// implements echo with -n option builtin
void	do_echo(char **args, int fd)
{
	int	idx;

	//(void) fd;
	if (args[1] && !ft_strcmp(args[1], "-n"))
	{
		idx = 1;
		while (args[++idx])
		{
			if (idx != 2)
				ft_putchar_fd(' ', fd);
			ft_putstr_fd(args[idx], fd);
		}
	}
	else
	{
		idx = 0;
		while (args[++idx])
		{
			if (idx != 1)
				ft_putchar_fd(' ', fd);
			ft_putstr_fd(args[idx], fd);
		}
		ft_putchar_fd('\n', fd);
	}
}
