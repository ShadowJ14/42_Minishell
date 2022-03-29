/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 20:46:12 by lprates           #+#    #+#             */
/*   Updated: 2022/03/29 01:29:13 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* implements cd builtin
** returns 1 on success
** returns 0 on failure
** needs to update old pwd because of cd -
** old pwd implemented but needs cleaning
** cd with no arguments is implemented but needs cleaning
** needs to implement "~" to expand variable
*/
int	do_cd(char *path, t_environment_element **environment_linked_list)
{
	t_environment_element	*environment_element;
	char					*old_pwd;

	environment_element = *environment_linked_list;
	if (!path || !ft_strcmp(path, "-"))
	{
		if (!path)
			path = malloc(sizeof(char *) + 1);
		old_pwd = malloc(sizeof(char *) + 1);
		if (!path || !old_pwd)
			return (0);
		while (environment_element != NULL)
		{
			if (!ft_strcmp(environment_element->name, "HOME") && ft_strcmp(path, "-"))
				path = environment_element->value;
			if (!ft_strcmp(environment_element->name, "OLDPWD"))
			{
				old_pwd = ft_strdup(environment_element->value);
				environment_element->value = getcwd(NULL, 0);
				if (!ft_strcmp(path, "-"))
				{
					if (!chdir(old_pwd))
						return (1);
				}
			}
			environment_element = environment_element->next_element;
		}
	}
	if (!chdir(path))
		return (1);
	write(1, "cd: no such file or directory: ", 32);
	write(1, path, ft_strlen(path));
	write(1, "\n", 2);
	return (0);
}
