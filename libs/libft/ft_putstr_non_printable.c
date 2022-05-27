/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:19:06 by lprates           #+#    #+#             */
/*   Updated: 2022/05/22 18:12:55 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	print_hex(int np)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (np >= 16)
	{
		print_hex(np / 16);
		print_hex(np % 16);
	}
	else
		write(STDOUT_FILENO, &hex[np], 1);
}

void	ft_putstr_non_printable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] <= 31 && str[i] > 0) || str[i] >= 127)
		{
			write(STDOUT_FILENO, "\\", 1);
			if (str[i] < 16)
				write(STDOUT_FILENO, "0", 1);
			print_hex(str[i]);
		}
		else
			write(STDOUT_FILENO, &str[i], 1);
		i++;
	}
}
