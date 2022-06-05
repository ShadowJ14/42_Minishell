/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 04:05:50 by lprates           #+#    #+#             */
/*   Updated: 2022/06/05 16:32:07 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_error_return(int error, int return_code)
{
	g_exit_code = error;
	return (return_code);
}

char	*set_error_return_null(int error, char *return_code)
{
	g_exit_code = error;
	return (return_code);
}
