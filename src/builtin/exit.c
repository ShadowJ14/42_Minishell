/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 20:46:36 by lprates           #+#    #+#             */
/*   Updated: 2022/04/10 16:00:45 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_exit(char **args)
{
	print_message("exit\n");
	if (args[1])
		exit(ft_atoi(args[1]));
	else
		exit(EXIT_SUCCESS);
}
