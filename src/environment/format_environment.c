/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_environment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 17:17:37 by rramos            #+#    #+#             */
/*   Updated: 2022/05/22 18:53:05 by rramos           ###   ########.fr       */
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
	t_env_elem *env_elem)
{
	size_t	name_index;
	size_t	value_index;

	name_index = 0;
	while (environment_variable[name_index] != '=' && \
		environment_variable[name_index] != '\0')
	{
		env_elem->name[name_index] = \
			environment_variable[name_index];
		name_index++;
	}
	env_elem->name[name_index] = '\0';
	if (environment_variable[name_index] == '\0')
		return ;
	name_index++;
	value_index = 0;
	while (environment_variable[name_index + value_index] != '\0')
	{
		env_elem->value[value_index] = \
			environment_variable[name_index + value_index];
		value_index++;
	}
	env_elem->value[value_index] = 0;
}

static void	add_element_to_env_linklist(t_env_elem \
	*env_linklist, t_env_elem *environment_new_element)
{
	t_env_elem	*env_elem;

	env_elem = env_linklist;
	while (env_elem->next_element != NULL)
		env_elem = env_elem->next_element;
	env_elem->next_element = environment_new_element;
}

t_env_elem	*format_environment(char **environment)
{
	t_env_elem	*env_linklist;
	t_env_elem	*env_elem;
	size_t		index;

	index = 0;
	env_linklist = NULL;
	while (environment[index] != NULL)
	{
		env_elem = allocate_memory(sizeof(*env_elem));
		env_elem->name = allocate_memory(\
			sizeof(char) \
				* (calculate_environment_name_length(environment[index]) + 1));
		env_elem->value = allocate_memory(\
			sizeof(char) \
				* (calculate_environment_value_length(environment[index]) + 1));
		env_elem->next_element = NULL;
		format_environment_variable(environment[index], env_elem);
		if (env_linklist == NULL)
			env_linklist = env_elem;
		else
			add_element_to_env_linklist(env_linklist, \
				env_elem);
		index++;
	}
	return (env_linklist);
}
