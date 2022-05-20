/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 13:09:03 by rramos            #+#    #+#             */
/*   Updated: 2022/05/21 00:14:19 by lprates          ###   ########.fr       */
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
# define HEREDOC 4
# define APPEND 5

typedef struct s_argument
{
	char	*name;
	bool	set_value;
	char	*value;
}	t_argument;

/*typedef struct s_global
{
	char	*input;
}	t_global;*/

// The environment variables are formatted by the program into a linked list.
// Each element of that linked list uses this structure which stores the name
// and the value of an environment variable, and a reference to the next element
// in the linked list.
typedef struct s_env_elem
{
	char				*name;
	char				*value;
	struct s_env_elem	*next_element;
}	t_env_elem;

typedef struct s_terminal
{
	int				amount_of_colums;
	int				amount_of_lines;
	struct termios	attributes;
	char			*environment_variable;
	int				file_descriptor;
	char			*path;
}	t_terminal;

// The s_cmd struct saves the cmd and the arguments
// from the user input, as well as the type of redirection/pipe.
typedef struct s_cmd
{
	char	*exec;
	char	**args;
	int		chain;
	int		pipe[2];
	char	*file;
}				t_cmd;

// testing
typedef enum quote
{
	NONE,
	SINGLE,
	DOUBLE,
	BACKSLASH,
	END
}	t_quote;

//t_global	g_global;

int g_exit_code;

// Function declarations.
void		*allocate_memory(size_t size);
size_t		calculate_string_length(char *string);
char		**convert_linked_list_to_array(t_env_elem *env_elem);
void		do_export(char **args, t_env_elem **env_linklist);
void		do_unset(char **args, t_env_elem **env_linklist);
t_env_elem	*format_environment(char **environment);
void		free_memory(void **memory_pointer);
void		handle_signals(void);
void		open_terminal(t_terminal *terminal);
void		print_error_message(char *error_message);
void		print_message(char *message);
char		*read_input_until_new_line(t_terminal terminal);
void		print_export(t_env_elem *env_linklist);

// lprates
int			msh_execute(t_cmd *cmd, t_env_elem *env_linklist);
t_cmd		*msh_split_line(char *line);
t_cmd		*realloc_n_initialize_cmd(t_cmd *cmd, int idx);
t_cmd		*local_split(char const *s);
void		set_builtin_funcs(char **builtin_funcs);
int			is_builtin(t_cmd *cmd);
char		**smart_split(char const *s, char *delim, t_cmd *cmd);
char		*expand_env_var(t_env_elem *env_linklist, char *env_name);
int			msh_execute_two(t_cmd *cmd, char **builtin_funcs, \
	t_env_elem *env_linklist);
char		*check_sysfunction(char *func);
int			forking(t_cmd *cmd, pid_t *pid, t_env_elem *env_linklist);
char		*expand_env_var_string(t_env_elem *env_linklist, \
	char *str, char *first);

//testing

t_quote		update_quote_status(char c, t_quote quote);
t_quote		update_quote_succes(int *i, t_quote quote, char **s1);
char		*word_modif_two(char *duplica, t_quote quote, t_quote prec, \
	t_env_elem *env_linklist);
char		*string_env(char *str, char *tmp, int *cur, \
	t_env_elem *env_linklist);

// builtins

int			execute_builtins(t_cmd *cmd, t_env_elem *env_linklist, \
	int *pid, int fd);
int			ft_built_in_pwd_fd(int fd);
void		do_echo(char **args, int pid);
int			do_exit(char **args, pid_t *pid);
int			do_cd(char *path, t_env_elem *env_linklist);

// sysfuncs



// cleanup

int			free_all(t_cmd **cmd);

#endif
