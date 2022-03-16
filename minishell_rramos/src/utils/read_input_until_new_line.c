/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_until_new_line.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 17:58:47 by rramos            #+#    #+#             */
/*   Updated: 2022/03/16 02:23:59 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
"Control + D" generates end-of-file (EOF), which causes the "read" function to
return 0 if no input is inserted, or return the amount of bytes inserted without
ending in a newline (since the "enter" key wasn't pressed).
*/

void	read_input_until_new_line(t_terminal terminal)
{
	char	*str;

	(void) terminal;
	str = readline("minishell> ");
	if (!str)
	{
		printf("exit\n");
		exit(-1);
	}
	else if (*str == '\0')
		free (str);
	else
		add_history(str);
	g_global.input = str;
}
