/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 20:46:36 by lprates           #+#    #+#             */
/*   Updated: 2022/05/22 18:48:15 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	ft_sup_int(char *str)
{
	long	res;
	int		sig;
	int		i;

	res = 0;
	sig = 1;
	i = 0;
	if (str[i] == '-')
	{
		i++;
		sig = -1;
	}
	while (str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
		if (res > 2147483648)
			return (2);
	}
	res = res * sig;
	if (res > 2147483647)
		return (2);
	return (0);
}

int	ft_non_int(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			write(STDERR_FILENO, "minishell: exit: ", 17);
			write(STDERR_FILENO, str, ft_strlen(str));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			return (2);
		}
		i++;
	}
	return (ft_sup_int(str));
}

int	do_exit(char **args, pid_t *pid)
{
	int	ret;

	ret = 0;
	print_message("exit\n");
	if (args[1] != NULL)
	{
		if (ft_non_int(args[1]))
		{
			//ft_clean_env();
			//free_all(first);
			free(pid);
			exit (2);
		}
		ret = ft_atoi(args[1]);
		if (args[2] != NULL)
		{
			write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
			g_exit_code = 1;
			return (2);
		}
		//free_in_builin(first, pid, ret);
		exit(ret);
	}
	else
	{
		exit(EXIT_SUCCESS);
	}
	return (0);
	//return (free_in_builin(first, pid, 0));
}
