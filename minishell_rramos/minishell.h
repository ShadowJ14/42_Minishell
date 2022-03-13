/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 13:09:03 by rramos            #+#    #+#             */
/*   Updated: 2022/03/12 17:19:16 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Include guard to avoid problems with multiple inclusion of the header file.
#ifndef MINISHELL_H

// Definition of the include guard macro.
# define MINISHELL_H

// Include the "open" function.
# include <fcntl.h>

// Include the "signal" function, and the "SIGINT" macro.
# include <signal.h>

// Include the "bool", "false" and "true" macros.
# include <stdbool.h>

// Include the "printf" function.
# include <stdio.h>

// Include the "exit" function, and the "EXIT_FAILURE" and "EXIT_SUCCESS"
// macros.
# include <stdlib.h>

// Include the "tgetent" function (implementation in the ncurses library).
# include <term.h>

// Include the "tcgetattr" and "tcsetattr" functions, the "TCSANOW" macro, and
// the "termios" structure.
# include <termios.h>

// Include the "read" and "write" functions, and the "STDIN_FILENO" and
// "STDOUT_FILENO" macros.
# include <unistd.h>

typedef struct s_global
{
	char	*input;
}	t_global;

// The environment variables are formatted by the program into a linked list.
// Each element of that linked list uses this structure which stores the name
// and the value of an environment variable, and a reference to the next element
// in the linked list.
typedef struct s_environment_element
{
	char							*name;
	char							*value;
	struct s_environment_element	*next_element;
}	t_environment_element;

typedef struct s_terminal
{
	int				amount_of_colums;
	int				amount_of_lines;
	struct termios	attributes;
	char			*environment_variable;
	int				file_descriptor;
	char			*path;
}	t_terminal;

t_global	g_global;

// Function declarations.
void					*allocate_memory(size_t size);
size_t					calculate_string_length(char *string);
t_environment_element	*format_environment(char **environment);
void					free_memory(char **memory_pointer);
void					handle_commands(void);
void					handle_signals(void);
void					open_terminal(t_terminal *terminal);
void					print_error_message(char *error_message);
void					print_message(char *message);
void					read_input_until_new_line(t_terminal terminal);

#endif
