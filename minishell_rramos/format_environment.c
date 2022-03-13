/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_environment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 17:17:37 by rramos            #+#    #+#             */
/*   Updated: 2022/03/13 11:59:54 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	calculate_environment_name_length(char *environment_variable)
{
	size_t	length;

	length = 0;
	while (environment_variable[length] != '=' \
		&& environment_variable[length] != '\0')
		length++;
	return (length);
}

static size_t	calculate_environment_value_length(char *environment_variable)
{
	size_t	index;
	size_t	length;

	index = 0;
	while (environment_variable[index] != '=' \
		&& environment_variable[index] != '\0')
		index++;
	length = 0;
	if (environment_variable[index + length] != '\0')
		index++;
	while (environment_variable[index + length] != '\0')
		length++;
	return (length);
}

static void	format_environment_variable(char *environment_variable, \
	t_environment_element *environment_element)
{
	size_t	name_index;
	size_t	value_index;

	name_index = 0;
	while (environment_variable[name_index] != '=' && \
		environment_variable[name_index] != '\0')
	{
		environment_element->name[name_index] = \
			environment_variable[name_index];
		name_index++;
	}
	environment_element->name[name_index] = '\0';
	if (environment_variable[name_index] == '\0')
		return ;
	name_index++;
	value_index = 0;
	while (environment_variable[name_index + value_index] != '\0')
	{
		environment_element->value[value_index] = \
			environment_variable[name_index + value_index];
		value_index++;
	}
	environment_element->value[value_index] = '\0';
}

static void	add_element_to_environment_linked_list(t_environment_element \
	*environment_linked_list, t_environment_element *environment_new_element)
{
	t_environment_element	*environment_element;

	environment_element = environment_linked_list;
	while (environment_element->next_element != NULL)
		environment_element = environment_element->next_element;
	environment_element->next_element = environment_new_element;
}

t_environment_element	*format_environment(char **environment)
{
	t_environment_element	*environment_linked_list;
	t_environment_element	*environment_element;
	size_t					index;

	index = 0;
	environment_linked_list = NULL;
	while (environment[index] != NULL)
	{
		environment_element = allocate_memory(sizeof(*environment_element));
		environment_element->name = allocate_memory(\
			sizeof(*environment_element->name) \
				* (calculate_environment_name_length(environment[index]) + 1));
		environment_element->value = allocate_memory(\
			sizeof(*environment_element->value) \
				* (calculate_environment_value_length(environment[index] + 1)));
		environment_element->next_element = NULL;
		format_environment_variable(environment[index], environment_element);
		if (environment_linked_list == NULL)
			environment_linked_list = environment_element;
		else
			add_element_to_environment_linked_list(environment_linked_list, \
				environment_element);
		index++;
	}
	return (environment_linked_list);
}
