/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_until_new_line.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 17:58:47 by rramos            #+#    #+#             */
/*   Updated: 2022/05/28 22:55:30 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
"Control + D" generates end-of-file (EOF), which causes the "read" function to
return 0 if no input is inserted, or return the amount of bytes inserted without
ending in a newline (since the "enter" key wasn't pressed).
*/

char	*read_input_until_new_line(void)
{
	char	*str;

	str = readline("minishell> ");
	if (!str)
	{
		ft_putstr_fd("exit\n", 1);
		exit(-1);
	}
	else if (*str == '\0')
	{
		free_memory((void **)&str);
		return (NULL);
	}
	else
		add_history(str);
	return (str);
}
