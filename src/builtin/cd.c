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

static char	*cd_home(char *path)
{
	char	*homestring;
	char	*home;

	homestring = NULL;
	home = expand_env_var("HOME");
	if (!home)
		return (NULL);
	if (!path)
		return (home);
	if (ft_strlen(path) > 1)
		homestring = ft_strjoin(home, &(*(path + 1)));
	else
		return (home);
	free(home);
	return (homestring);
}

/* implements cd builtin
** returns EXIT_SUCCESS on success
** returns EXIT_FAILURE on failure
** needs to update old pwd because of cd -
** old pwd implemented but needs cleaning
** cd with no arguments is implemented but needs cleaning
** added OLDPWD and PWD update
** needs to implement "~" to expand variable - done
*/
int	do_cd(char *path)
{
	t_env_elem	*env_elem;
	int			change_failed;
	char		*old;

	env_elem = env_singleton(NULL);
	old = getcwd(NULL, 0);
	if (old == NULL)
		return (set_error_return(errno, EXIT_FAILURE));
	if (!path || ft_strchr(path, '~'))
		path = cd_home(path);
	if (!ft_strcmp(path, "-"))
		path = expand_env_var("OLDPWD");
	while (env_elem != NULL)
	{
		if (!ft_strcmp(env_elem->name, "OLDPWD"))
		{
			free(env_elem->value);
			env_elem->value = old;
		}
		if (!ft_strcmp(env_elem->name, "PWD"))
		{
			change_failed = chdir(path);
			free(env_elem->value);
			env_elem->value = getcwd(NULL, 0);
			if (env_elem->value == NULL)
				return (set_error_return(errno, EXIT_FAILURE));
		}
		env_elem = env_elem->next_element;
	}
	if (!change_failed)
		return (set_error_return(EXIT_SUCCESS, EXIT_SUCCESS));
	perror("minishell");
	return (set_error_return(EXIT_FAILURE, EXIT_FAILURE));
}
