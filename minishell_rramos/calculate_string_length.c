/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_string_length.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:31:30 by rramos            #+#    #+#             */
/*   Updated: 2022/03/13 11:29:36 by rramos           ###   ########.fr       */
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
