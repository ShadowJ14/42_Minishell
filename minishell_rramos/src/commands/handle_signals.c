/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 00:38:33 by rramos            #+#    #+#             */
/*   Updated: 2022/03/13 11:29:38 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
"Control + C" generates the signal SIGINT.
"Control + \" generates the signal SIGQUIT.
*/

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
		print_message("\n");
}

void	handle_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
