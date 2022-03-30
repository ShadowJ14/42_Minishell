/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 20:46:12 by lprates           #+#    #+#             */
/*   Updated: 2022/03/30 01:50:13 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* implements cd builtin
** returns 1 on success
** returns 0 on failure
** needs to update old pwd because of cd -
** old pwd implemented but needs cleaning
** cd with no arguments is implemented but needs cleaning
** added OLDPWD and PWD update
** needs to implement "~" to expand variable
*/
int	do_cd(char *path, t_environment_element *environment_linked_list)
{
	t_environment_element	*environment_element;

	environment_element = environment_linked_list;
	if (!path)
	{
		path = expand_env_var(environment_linked_list, "HOME");
		if (!path)
			return (0);
	}
	if (!ft_strcmp(path, "-"))
		path = expand_env_var(environment_linked_list, "OLDPWD");
	while (environment_element != NULL)
	{
		if (!ft_strcmp(environment_element->name, "OLDPWD"))
			environment_element->value = getcwd(NULL, 0);
		if (!ft_strcmp(environment_element->name, "PWD"))
			environment_element->value = path;
		environment_element = environment_element->next_element;
	}
	if (!chdir(path))
		return (1);
	write(1, "cd: no such file or directory: ", 32);
	write(1, path, ft_strlen(path));
	write(1, "\n", 2);
	return (0);
}
