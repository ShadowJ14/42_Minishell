/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:23:26 by rramos            #+#    #+#             */
/*   Updated: 2022/04/10 15:25:26 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_env(t_environment_element *environment_element)
{
	while (environment_element != NULL)
	{
		print_message(environment_element->name);
		print_message("=");
		print_message(environment_element->value);
		print_message("\n");
		environment_element = environment_element->next_element;
	}
}
