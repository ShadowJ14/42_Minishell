/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_string_length.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:31:30 by rramos            #+#    #+#             */
/*   Updated: 2022/05/29 16:59:27 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	calculate_string_length(char *string)
{
	size_t	string_length;

	string_length = 0;
	if (string != NULL)
		while (string[string_length] != '\0')
			string_length++;
	return (string_length);
}
