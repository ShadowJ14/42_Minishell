/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 20:46:12 by lprates           #+#    #+#             */
/*   Updated: 2022/05/22 18:21:34 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cd_home(char *path, t_env_elem *env_linklist)
{
	char	*homestring;
	char	*home;

	homestring = NULL;
	home = expand_env_var(env_linklist, "HOME");
	if (!home)
		return (NULL);
	if (!path)
		return (home);
	if (ft_strlen(path) > 1)
		homestring = ft_strjoin(home, &(*(path + 1)));
	else
		homestring = home;
	free(path);
	return (homestring);
}

/* implements cd builtin
** returns 1 on success
** returns 0 on failure
** needs to update old pwd because of cd -
** old pwd implemented but needs cleaning
** cd with no arguments is implemented but needs cleaning
** added OLDPWD and PWD update
** needs to implement "~" to expand variable - done
*/
int	do_cd(char *path, t_env_elem *env_linklist)
{
	t_env_elem	*env_elem;

	env_elem = env_singleton(NULL);
	if (!path || ft_strchr(path, '~'))
		path = cd_home(path, env_elem);
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
	print_message("cd: no such file or directory: ");
	print_message(path);
	print_message("\n");
	return (0);
}
