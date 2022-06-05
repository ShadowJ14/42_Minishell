/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 13:09:03 by rramos            #+#    #+#             */
/*   Updated: 2022/05/22 22:47:55 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Include guard to avoid problems with multiple inclusion of the header file.
#ifndef MINISHELL_H

// Definition of the include guard macro.
# define MINISHELL_H

// Include the "errno" global variable.
# include <errno.h>

// Include the "open" function.
# include <fcntl.h>

# include <curses.h>

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
# include <termcap.h>

// Include the "read" and "write" functions, and the "STDERR_FILENO",
// "STDIN_FILENO", and "STDOUT_FILENO" macros.
# include <unistd.h>

# include "../libs/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

# define ERROR -1

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
	struct termios	attributes_new;
	char			*buffer;
	char			*keys_on;
	char			*keys_off;
	char			*up_arrow;
	char			*down_arrow;
	char			*backspace;
	char			*del_line;
	char			*set_cursor_begin;
	int				file_descriptor;
	char			*path;
}	t_terminal;

// The s_cmd struct saves the cmd and the arguments
// from the user input, as well as the type of redirection/pipe.
typedef struct s_cmd
{
	int		exec;
	char	**args;
	int		chain;
	int		pipe[2];
	char	*file;
	char	*file_name;
	int		no_expand;
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

int	g_exit_code;

// Function declarations.
void		*alloc_mem(size_t size);
size_t		calculate_string_length(char *string);
char		**convert_linked_list_to_array(t_env_elem *env_elem);
t_env_elem	*format_environment(char **environment);
void		free_memory(void **memory_pointer);
void		handle_signals(void);
void		open_terminal(t_terminal *terminal);
void		print_error_message(char *error_message);
void		print_message(char *message);
char		*read_input_until_new_line(void);
t_env_elem	*env_singleton(t_env_elem *set_env_linklist);

int			msh_execute(t_cmd *cmd);
t_cmd		*msh_split_line(char *line);
t_cmd		*realloc_n_initialize_cmd(t_cmd *cmd, int idx);
t_cmd		*local_split(char const *s);
void		set_builtin_funcs(char **builtin_funcs);
int			is_builtin(t_cmd *cmd);
char		**smart_split(char const *s, t_cmd *cmd);
char		*expand_env_var(char *env_name);
int			msh_execute_two(t_cmd *cmd, char **builtin_funcs, \
	t_env_elem *env_linklist);
char		*check_sysfunction(char *func);
int			forking(t_cmd *cmd, pid_t *pid);

// parsing

t_quote		update_quote_status(char c, t_quote quote);
t_quote		update_quote_succes(int *i, t_quote quote, char **s1);
char		*word_modif_two(char *duplica, t_quote quote, t_quote prec);
char		*string_env(char *str, char *tmp, int *cur);
int			set_chain(char *tmp);

// builtins

int			execute_builtins(t_cmd *cmd, int *pid, int fd);
int			ft_built_in_pwd_fd(int fd);
void		do_echo(char **args, int pid);
int			do_exit(char **args, pid_t *pid);
int			do_cd(char *path);
void		do_unset(char **args);
void		do_export(char **args);
void		print_export(void);
int			f_strdup(t_env_elem *env_linklist, t_argument *argument);

// redirections

int			create_heredoc_fd(t_cmd *cmd);
int			random_char(void);
char		*create_random_name(void);
int			open_pipe(t_cmd **cmd);
int			init_pipe(int **nfd, int i, t_cmd *cur, t_cmd *cmd);
int			redirect_file_in(t_cmd *cmd, int chain);
int			redirect_file_out(t_cmd *cmd, int chain);
int			wait_pid(t_cmd **cmd, pid_t *pid);

// cleanup

int			free_all(char *env);
void		free_both(char *s1, char *s2);
char		*free_str_ret_null(char *s1);
int			free_array(void **str);
void		free_env_llist(t_env_elem *env_llist);

// utils
int			cmd_len(t_cmd *cur);
void		update_shlvl(void);
char		*move_to_end_redirect(char *s, char delim, char *from);
char		*move_to_delim(char *s, char delim, char *from);
void		set_args(char **ret, char const *s, char *from, int idx);

// commands

void		close_fd_all(t_cmd **cmd);
int			open_fd(t_cmd *cmd);
t_cmd		*cmd_singleton(t_cmd *set_cmd);

// environment

char		*word_will_double(char *str, int *cur, char *s1);
char		*word_will_unquote(char *str, int *cur, char *s1);
char		*get_env(int *cur, char *str);
char		*alloc_dollar(int *cur);

// terminal

//void		change_terminal_attributes(t_terminal *terminal);
void		turn_off_canonical_mode(t_terminal *terminal);
void		turn_on_canonical_mode(t_terminal *terminal);
int			termios_change(bool echo_ctl_chr);

// error
int			set_error_return(int error, int return_code);
char		*set_error_return_null(int error, char *return_code);

// signals
void		ft_sigint(int signal);

#endif
