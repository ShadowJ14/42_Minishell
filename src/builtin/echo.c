/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 20:44:27 by lprates           #+#    #+#             */
/*   Updated: 2022/03/13 20:45:07 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// implements echo with -n option builtin
void	do_echo(char **args)
{
	int	idx;

	if (args[1] && !ft_strcmp(args[1], "-n"))
	{
		idx = 1;
		while (args[++idx])
		{
			if (idx != 2)
				write(1, " ", 1);
			write(1, args[idx], ft_strlen(args[idx]));
		}
	}
	else
	{
		idx = 0;
		while (args[++idx])
		{
			if (idx != 1)
				write(1, " ", 1);
			write(1, args[idx], ft_strlen(args[idx]));
		}
		write(1, "\n", 1);
	}
}
