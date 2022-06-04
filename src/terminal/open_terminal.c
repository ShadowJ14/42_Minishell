/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_terminal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 00:28:50 by rramos            #+#    #+#             */
/*   Updated: 2022/06/04 16:12:44 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_putint(int c)
{
	return (write(1, &c, 1));
}

void	turn_on_canonical_mode(t_terminal *terminal)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &terminal->attributes) == -1)
		print_error_message("Failure setting the terminal attributes.\n");

}

void	turn_off_canonical_mode(t_terminal *terminal)
{
	terminal->attributes_new = terminal->attributes;
	terminal->attributes_new.c_lflag &= ~ICANON;
	terminal->attributes_new.c_lflag &= ~ECHOCTL;
	terminal->attributes_new.c_lflag &= ~ISIG;
	terminal->attributes_new.c_lflag &= ~IEXTEN;
	terminal->attributes_new.c_iflag &= ~IXON;
	terminal->attributes_new.c_cc[VMIN] = 1;
	terminal->attributes_new.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &terminal->attributes_new) == -1)
		print_error_message("Failure setting the terminal attributes.\n");
}

int	has_capabilities(t_terminal *terminal)
{
	int	check;

	terminal->keys_on = tgetstr("ks", &terminal->buffer);
	if (terminal->keys_on)
		tputs(terminal->keys_on, 1, ft_putint);
	terminal->keys_off = tgetstr("ke", &terminal->buffer);
	terminal->up_arrow = tgetstr("ku", &terminal->buffer);
	terminal->down_arrow = tgetstr("kd", &terminal->buffer);
	terminal->backspace = ft_strdup("\x7f");
	terminal->del_line = tgetstr("dl", &terminal->buffer);
	terminal->set_cursor_begin = tgetstr("cr", &terminal->buffer);
	if (!terminal->keys_on || !terminal->keys_off
		|| !terminal->up_arrow || !terminal->down_arrow
		|| !terminal->backspace || !terminal->del_line
		|| !terminal->set_cursor_begin)
		check = 0;
	else
		check = 1;
	return (check);
}

static void	change_terminal_attributes(t_terminal *terminal)
{
	char	*term_type;

	ft_bzero(terminal, sizeof(t_terminal));
	if (tcgetattr(STDIN_FILENO, &terminal->attributes) == -1)
		print_error_message("Failure getting the terminal attributes.\n");
	term_type = expand_env_var("TERM");
	if (term_type == NULL)
		print_error_message("Failure getting the terminal environment" \
			" variable.\n");
	if (tgetent(terminal->buffer, term_type) <= 0)
		print_error_message("The terminfo database could not be found.\n");
	if (!has_capabilities(terminal))
		print_error_message("No capabilities - terminal.\n");
	//terminal->attributes.c_lflag &= ~(ECHOCTL);
	/*if (tcsetattr(terminal->file_descriptor, TCSANOW, &terminal->attributes) \
		== -1)
		print_error_message("Failure setting the terminal attributes.\n");*/
	free(term_type);
}

void	open_terminal(t_terminal *terminal)
{
	
	
	/*terminal->path = ttyname(STDOUT_FILENO);
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
			" of the terminal.\n");*/
	change_terminal_attributes(terminal);
}
