/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 04:06:24 by lprates           #+#    #+#             */
/*   Updated: 2022/03/12 04:01:18 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <signal.h>
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

typedef struct s_command
{
	char	*command;
	char	*args;
	int		chain;
}				t_command;

t_command	*local_split(char const *s, char *delim);
char	*check_sysfunction(char *func);
int		exec_sysfunction(char **args);
void	set_builtin_funcs(char **builtin_funcs);
int		builtin(char *cmd, char **builtin_funcs, char **args);
t_command	*get_commands(char *line);
#endif
