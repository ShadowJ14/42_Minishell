/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 13:09:03 by rramos            #+#    #+#             */
/*   Updated: 2022/03/30 01:50:13 by lprates          ###   ########.fr       */
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

# include "../libs/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

# define BUILTIN_FUNCS_NB 7
# define PIPE 1
# define REDIRECTI 2
# define REDIRECTO 3
# define APPENDI 4
# define APPENDO 5

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

// The s_command struct saves the command and the arguments
// from the user input, as well as the type of redirection/pipe.
typedef struct s_command
{
	char	*command;
	char	**args;
	int		chain;
}				t_command;

t_global	g_global;

// Function declarations.
void					*allocate_memory(size_t size);
size_t					calculate_string_length(char *string);
void					do_export(char **args, \
	t_environment_element *environment_linked_list);
void					do_unset(char **args, \
	t_environment_element *environment_linked_list);
t_environment_element	*format_environment(char **environment);
void					free_memory(char **memory_pointer);
void					handle_signals(void);
void					open_terminal(t_terminal *terminal);
void					print_error_message(char *error_message);
void					print_message(char *message);
char					*read_input_until_new_line(t_terminal terminal);

// lprates
int						msh_execute(t_command *command, char **builtin_funcs, \
	t_environment_element *environment_linked_list);
t_command				*msh_split_line(char *line);
t_command				*realloc_n_initialize_cmd(t_command *cmd, int idx);
t_command				*local_split(char const *s, char *delim);
void					do_echo(char **args);
int						do_cd(char *path, \
	t_environment_element *environment_linked_list);
void					do_exit(char **args);
void					set_builtin_funcs(char **builtin_funcs);
int						exec_sysfunction(t_command *command);
int						builtin(t_command *command, char **builtin_funcs, \
	t_environment_element *environment_linked_list);
char					**smart_split(char const *s, char *delim);
char					*expand_env_var(t_environment_element *environment_linked_list,
							char *env_name);

#endif
