/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:27:03 by rramos            #+#    #+#             */
/*   Updated: 2022/05/22 18:49:48 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_env_elem *env_linklist)
{
	t_env_elem	*env_elem;

	env_elem = env_linklist;
	while (env_elem != NULL)
	{
		print_message(env_elem->name);
		print_message("=");
		if (env_elem->value[0] == '\0')
			print_message("''");
		else
			print_message(env_elem->value);
		print_message("\n");
		env_elem = env_elem->next_element;
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
	while (index_2 < index_1)
	{
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
	while (arg[index_1 + index_2] != '\0')
	{
		argument->value[index_2] = arg[index_1 + index_2];
		index_2++;
	}
	argument->value[index_2] = '\0';
	return (argument);
}

static void	set_args(char **args, \
	t_env_elem **env_linklist)
{
	t_argument	*argument;
	t_env_elem	**env_elem;
	size_t		index;
	t_env_elem	*new_env_elem;

	index = 1;
	while (args[index] != NULL)
	{
		argument = get_argument(args[index]);
		env_elem = env_linklist;
		while (*env_elem != NULL)
		{
			if (!ft_strcmp((*env_elem)->name, argument->name))
			{
				if (argument->set_value)
					(*env_elem)->value = argument->value;
				break ;
			}
			if ((*env_elem)->next_element == NULL)
				break ;
			env_elem = &(*env_elem)->next_element;
		}
		if (ft_strcmp((*env_elem)->name, argument->name))
		{
			new_env_elem = allocate_memory(sizeof(*new_env_elem));
			new_env_elem->name = argument->name;
			if (argument->value)
				new_env_elem->value = argument->value;
			else
				new_env_elem->value = 0;
			(*env_elem)->next_element = new_env_elem;
		}
		index++;
	}
}

// implements export builtin
void	do_export(char **args, t_env_elem **env_linklist)
{
	if (args[1] == NULL)
	{
		print_export(*env_linklist);
		return ;
	}
	verify_args(args);
	set_args(args, env_linklist);
}
