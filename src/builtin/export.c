/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:27:03 by rramos            #+#    #+#             */
/*   Updated: 2022/04/03 16:06:14 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_environment_element *environment_linked_list)
{
	t_environment_element	*environment_element;

	environment_element = environment_linked_list;
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
}

static void	verify_args(char **args)
{
	size_t	index;

	index = 1;
	while (args[index] != NULL)
	{
		if (!(ft_isalpha(args[index][0]) || args[index][0] == '_'))
			print_error_message(ft_strjoin(ft_strjoin("export: not an" \
				" identifier: ", args[index]), "\n"));
		index++;
	}
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
	while (index_2 < index_1) {
		argument->name[index_2] = arg[index_2];
		index_2++;
	}
	argument->name[index_2] = '\0';
	argument->value = allocate_memory(sizeof(*(argument->value)) * \
		(calculate_string_length(arg) - index_1));
	argument->set_value = false;
	if (arg[index_1] == '=')
	{
		index_1++;
		argument->set_value = true;
	}
	index_2 = 0;
	while (arg[index_1 + index_2] != '\0') {
		argument->value[index_2] = arg[index_1 + index_2];
		index_2++;
	}
	argument->value[index_2] = '\0';
	return (argument);
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
		while (*environment_element != NULL)
		{
			if (!ft_strcmp((*environment_element)->name, argument->name))
			{
				if (argument->set_value)
					(*environment_element)->value = argument->value;
				break ;
			}
			if ((*environment_element)->next_element == NULL)
				break ;
			environment_element = &(*environment_element)->next_element;
		}
		if (ft_strcmp((*environment_element)->name, argument->name))
		{
			new_environment_element = allocate_memory(sizeof(*new_environment_element));
			new_environment_element->name = argument->name;
			if (argument->value)
				new_environment_element->value = argument->value;
			else
				new_environment_element->value = 0;
			(*environment_element)->next_element = new_environment_element;
		}
		index++;
	}
}

// implements export builtin
void	do_export(char **args, t_environment_element **environment_linked_list)
{
	if (args[1] == NULL)
	{
		print_export(*environment_linked_list);
		return ;
	}
	verify_args(args);
	set_args(args, environment_linked_list);
}
