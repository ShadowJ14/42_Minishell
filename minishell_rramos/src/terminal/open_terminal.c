/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_terminal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 00:28:50 by rramos            #+#    #+#             */
/*   Updated: 2022/03/13 11:29:45 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_terminal_attributes(t_terminal *terminal)
{
	if (tcgetattr(terminal->file_descriptor, &terminal->attributes) == -1)
		print_error_message("Failure getting the terminal attributes.\n");
	terminal->attributes.c_lflag &= ~(ECHO | ICANON | ISIG);
	if (tcsetattr(terminal->file_descriptor, TCSANOW, &terminal->attributes) \
		== -1)
		print_error_message("Failure setting the terminal attributes.\n");
}

void	open_terminal(t_terminal *terminal)
{
	terminal->environment_variable = getenv("TERM");
	if (terminal->environment_variable == NULL)
		print_error_message("Failure getting the terminal environment" \
			" variable.\n");
	if (tgetent(NULL, terminal->environment_variable) == -1)
		print_error_message("The terminfo database could not be found.\n");
	terminal->path = ttyname(STDOUT_FILENO);
	if (terminal->path == NULL)
		print_error_message("Failure getting the path of the terminal.\n");
	terminal->file_descriptor = open(terminal->path, O_RDWR);
	if (terminal->file_descriptor == -1)
		print_error_message("Failure opening the terminal.\n");
	if (isatty(terminal->file_descriptor) == 0)
		print_error_message("Failure: the file descriptor is not an open file" \
			" descriptor referring to a terminal.\n");
	terminal->amount_of_colums = tgetnum("co");
	terminal->amount_of_lines = tgetnum("li");
	if (terminal->amount_of_colums == -1 || terminal->amount_of_lines == -1)
		print_error_message("Failure getting the amount of columns and lines" \
			" of the terminal.\n");
	change_terminal_attributes(terminal);
}
