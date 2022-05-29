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
	t_argument	*arg2;
	size_t		i1;
	size_t		index_2;

	i1 = 0;
	while (arg[i1] != '=' && arg[i1] != '\0')
		i1++;
	arg2 = alloc_mem(sizeof(*arg2));
	arg2->name = alloc_mem(sizeof(*(arg2->name)) * (i1 + 1));
	index_2 = -1;
	while (++index_2 < i1)
		arg2->name[index_2] = arg[index_2];
	arg2->name[index_2] = '\0';
	arg2->value = alloc_mem(sizeof(*(arg2->value)) * (ft_strlen(arg) - i1));
	arg2->set_value = false;
	if (arg[i1] == '=')
	{
		i1++;
		arg2->set_value = true;
	}
	index_2 = -1;
	while (arg[i1 + ++index_2] != '\0')
		arg2->value[index_2] = arg[i1 + index_2];
	arg2->value[index_2] = '\0';
	return (arg2);
}

static t_env_elem	*allocate_new_node(t_argument *argument)
{
	t_env_elem	*new_env_linklist;

	new_env_linklist = alloc_mem(sizeof(*new_env_linklist));
	new_env_linklist->name = argument->name;
	if (argument->value)
		new_env_linklist->value = argument->value;
	else
		new_env_linklist->value = 0;
	return (new_env_linklist);
}

static void	set_args(char **args, \
	t_env_elem **env_linklist)
{
	t_argument	*argument;
	size_t		index;

	index = 0;
	while (args[++index] != NULL)
	{
		argument = get_argument(args[index]);
		while (*env_linklist != NULL)
		{
			if (!ft_strcmp((*env_linklist)->name, argument->name))
			{
				if (argument->set_value)
					(*env_linklist)->value = argument->value;
				break ;
			}
			if ((*env_linklist)->next_element == NULL)
				break ;
			env_linklist = &(*env_linklist)->next_element;
		}
		if (ft_strcmp((*env_linklist)->name, argument->name))
			(*env_linklist)->next_element = allocate_new_node(argument);
	}
}

// implements export builtin
void	do_export(char **args)
{
	t_env_elem	*env_linklist;

	env_linklist = env_singleton(NULL);
	if (args[1] == NULL)
	{
		print_export();
		return ;
	}
	verify_args(args);
	set_args(args, &env_linklist);
}
