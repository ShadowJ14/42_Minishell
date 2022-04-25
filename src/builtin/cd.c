/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 20:46:12 by lprates           #+#    #+#             */
/*   Updated: 2022/04/24 23:22:27 by lprates          ###   ########.fr       */
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
int	do_cd(char *path, t_env_elem *env_linklist)
{
	t_env_elem	*env_elem;

	env_elem = env_linklist;
	if (!path)
	{
		path = expand_env_var(env_linklist, "HOME");
		if (!path)
			return (0);
	}
	if (!ft_strcmp(path, "-"))
		path = expand_env_var(env_linklist, "OLDPWD");
	while (env_elem != NULL)
	{
		if (!ft_strcmp(env_elem->name, "OLDPWD"))
			env_elem->value = getcwd(NULL, 0);
		if (!ft_strcmp(env_elem->name, "PWD"))
			env_elem->value = path;
		env_elem = env_elem->next_element;
	}
	if (!chdir(path))
		return (1);
	write(1, "cd: no such file or directory: ", 32);
	write(1, path, ft_strlen(path));
	write(1, "\n", 2);
	return (0);
}
