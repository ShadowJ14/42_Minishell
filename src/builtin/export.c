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

static int	verify_args(char **args)
{
	size_t	index;

	index = 1;
	while (args[index] != NULL)
	{
		if (!(ft_isalpha(args[index][0]) || args[index][0] == '_'))
		{
			g_exit_code = 1;
			print_error_message(ft_strjoin(ft_strjoin("minishell: export: `", \
				args[index]), "': not a valid identifier\n"));
			return (EXIT_FAILURE);
		}
		if (!ft_strchr(args[index], '='))
			set_error_return(0, EXIT_SUCCESS);
		index++;
	}
	g_exit_code = 0;
	return (EXIT_SUCCESS);
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
	arg2->value = alloc_mem(sizeof(*(arg2->value)) * (ft_strlen(arg) - i1 + 1));
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
	new_env_linklist->name = ft_strdup(argument->name);
	if (argument->value)
		new_env_linklist->value = ft_strdup(argument->value);
	else
		new_env_linklist->value = 0;
	free_both(argument->name, argument->value);
	free(argument);
	return (new_env_linklist);
}

static void	set_arguments(char **args, \
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
				if (!args[index + 1])
					return ;
				break ;
			}
			if ((*env_linklist)->next_element == NULL)
				break ;
			env_linklist = &(*env_linklist)->next_element;
		}
		if (ft_strcmp((*env_linklist)->name, argument->name))
			(*env_linklist)->next_element = allocate_new_node(argument);
	}
	if ((*env_linklist)->next_element != NULL)
		env_linklist = &(*env_linklist)->next_element;
	(*env_linklist)->next_element = 0;
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
	if (verify_args(args))
		return ;
	set_arguments(args, &env_linklist);
}
