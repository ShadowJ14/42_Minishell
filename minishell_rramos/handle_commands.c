/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 22:05:21 by rramos            #+#    #+#             */
/*   Updated: 2022/03/05 12:09:44 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Work in progress. The function needs to be improved for when there are spaces,
quotes, and such.
*/

static void	handle_exit_command(void)
{
	if (g_global.input[0] == 'e' && g_global.input[1] == 'x' \
		&& g_global.input[2] == 'i' && g_global.input[3] == 't' \
		&& (g_global.input[4] == ' ' || g_global.input[4] == '\0'))
	{
		free_memory(&g_global.input);
		exit(EXIT_SUCCESS);
	}
}

void	handle_commands(void)
{
	handle_exit_command();
}
