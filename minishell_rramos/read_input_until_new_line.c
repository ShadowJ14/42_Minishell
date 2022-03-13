/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_until_new_line.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 17:58:47 by rramos            #+#    #+#             */
/*   Updated: 2022/03/13 16:40:23 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
"Control + D" generates end-of-file (EOF), which causes the "read" function to
return 0 if no input is inserted, or return the amount of bytes inserted without
ending in a newline (since the "enter" key wasn't pressed).
*/

static void	handle_control_d(const size_t amount_of_bytes_to_read, \
	ssize_t amount_of_bytes_read, char *buffer)
{
	if (false && (amount_of_bytes_read == 0 || \
		(amount_of_bytes_read < (ssize_t)amount_of_bytes_to_read && \
		buffer[amount_of_bytes_read - 1] != '\n')))
	{
		free_memory(&g_global.input);
		free_memory(&buffer);
		exit (EXIT_SUCCESS);
	}
}

static void	add_buffer_to_input(ssize_t amount_of_bytes_read, char *buffer)
{
	ssize_t	index_1;
	ssize_t	index_2;
	char	*input;

	input = allocate_memory(sizeof(*input) \
		* (calculate_string_length(g_global.input) + amount_of_bytes_read + 1));
	index_1 = 0;
	if (g_global.input != NULL)
	{
		while (g_global.input[index_1] != '\0')
		{
			input[index_1] = g_global.input[index_1];
			index_1++;
		}
	}
	free_memory(&g_global.input);
	index_2 = 0;
	while (index_2 < amount_of_bytes_read)
	{
		input[index_1 + index_2] = buffer[index_2];
		index_2++;
	}
	input[index_1 + index_2] = '\0';
	g_global.input = input;
}

static void	print_input(ssize_t *index, ssize_t amount_of_bytes_read,
	char *buffer)
{
	while (*index < amount_of_bytes_read)
	{
		if (buffer[*index] == '\n')
			break ;
		(*index)++;
	}
	write(STDOUT_FILENO, buffer, *index + 1);
}

void	read_input_until_new_line(t_terminal terminal)
{
	ssize_t			amount_of_bytes_read;
	const size_t	amount_of_bytes_to_read = 1024;
	char			*buffer;
	ssize_t			index;

	buffer = allocate_memory(sizeof(*buffer) * amount_of_bytes_to_read);
	while (true)
	{
		amount_of_bytes_read = read(terminal.file_descriptor, buffer, \
			amount_of_bytes_to_read);
		handle_control_d(amount_of_bytes_to_read, amount_of_bytes_read, buffer);
		add_buffer_to_input(amount_of_bytes_read, buffer);
		index = 0;
		print_input(&index, amount_of_bytes_read, buffer);
		if (buffer[index] == '\n')
			break ;
	}
	index = 0;
	while (g_global.input[index] != '\n')
		index++;
	write(STDOUT_FILENO, g_global.input, index + 1);
	free_memory(&buffer);
}
