/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:03:15 by rramos            #+#    #+#             */
/*   Updated: 2022/04/10 18:13:38 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(char **args)
{
	char	*error_message;
	size_t	index;

	index = 1;
	while (args[index] != NULL)
	{
		if (!(ft_isalpha(args[index][0]) || args[index][0] == '_'))
		{
			error_message = ft_strjoin(ft_strjoin(\
				"export: not an identifier: ", args[index]), "\n");
			print_message(error_message);
			free_memory((void **)&error_message);
			exit(EXIT_FAILURE);
		}
		index++;
	}
}
