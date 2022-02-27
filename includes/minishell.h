/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 04:06:24 by lprates           #+#    #+#             */
/*   Updated: 2022/02/27 18:33:49 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
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

char	**local_split(char const *s, char *delim);
char	*check_sysfunction(char *func);
int		exec_sysfunction(char **args);
void	set_builtin_funcs(char **builtin_funcs);
int		builtin(char *cmd, char **builtin_funcs, char **args);

#endif
