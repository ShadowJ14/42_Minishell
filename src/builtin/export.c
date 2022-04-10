/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:27:03 by rramos            #+#    #+#             */
/*   Updated: 2022/04/10 17:04:17 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_value(char *arg, t_argument *argument, \
	size_t index_1, size_t index_2)
{
	argument->value = allocate_memory(sizeof(*(argument->value)) * \
		(calculate_string_length(arg) - index_1));
	argument->set_value = false;
	if (arg[index_1] == '=')
	{
		index_1++;
		argument->set_value = true;
	}
	index_2 = 0;
	while (arg[index_1 + index_2] != '\0')
	{
		argument->value[index_2] = arg[index_1 + index_2];
		index_2++;
	}
	argument->value[index_2] = '\0';
}

static t_argument	*get_argument(char *arg)
{
	t_argument	*argument;
	size_t		index_1;
	size_t		index_2;

	index_1 = 0;
	while (arg[index_1] != '=' && arg[index_1] != '\0')
		index_1++;
	argument = allocate_memory(sizeof(*argument));
	argument->name = allocate_memory(sizeof(*(argument->name)) * (index_1 + 1));
	index_2 = 0;
	while (index_2 < index_1)
	{
		argument->name[index_2] = arg[index_2];
		index_2++;
	}
	argument->name[index_2] = '\0';
	get_value(arg, argument, index_1, index_2);
	return (argument);
}

static void	replace_argument_value(t_argument *argument, \
	t_environment_element ***environment_element)
{
	while (**environment_element != NULL)
	{
		if (!ft_strcmp((**environment_element)->name, argument->name))
		{
			if (argument->set_value)
				(**environment_element)->value = argument->value;
			break ;
		}
		if ((**environment_element)->next_element == NULL)
			break ;
		*environment_element = &(**environment_element)->next_element;
	}
}

static void	set_args(char **args, \
	t_environment_element **environment_linked_list)
{
	t_argument				*argument;
	t_environment_element	**environment_element;
	size_t					index;
	t_environment_element	*new_environment_element;

	index = 1;
	while (args[index] != NULL)
	{
		argument = get_argument(args[index]);
		environment_element = environment_linked_list;
		replace_argument_value(argument, &environment_element);
		if (ft_strcmp((*environment_element)->name, argument->name))
		{
			new_environment_element = \
				allocate_memory(sizeof(*new_environment_element));
			new_environment_element->name = argument->name;
			new_environment_element->value = argument->value;
			(*environment_element)->next_element = new_environment_element;
		}
		index++;
	}
}

// implements export builtin
void	do_export(char **args, t_environment_element **environment_linked_list)
{
	t_environment_element	*environment_element;

	if (args[1] == NULL)
	{
		environment_element = *environment_linked_list;
		while (environment_element != NULL)
		{
			print_message(environment_element->name);
			print_message("=");
			if (environment_element->value[0] == '\0')
				print_message("''");
			else
				print_message(environment_element->value);
			print_message("\n");
			environment_element = environment_element->next_element;
		}
		return ;
	}
	print_export(args);
	set_args(args, environment_linked_list);
}
