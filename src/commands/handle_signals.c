/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 00:38:33 by rramos            #+#    #+#             */
/*   Updated: 2022/04/09 17:50:21 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
"Control + C" generates the signal SIGINT.
"Control + \" generates the signal SIGQUIT.
"Control + D" generates the signal SIGTERM.
		print_message("\n");
*/

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
		printf("minishell> \n");
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

void	handle_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, signal_handler);
}
