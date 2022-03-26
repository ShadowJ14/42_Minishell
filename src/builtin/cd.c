/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 20:46:12 by lprates           #+#    #+#             */
/*   Updated: 2022/03/13 20:46:21 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* implements cd builtin
** returns 1 on success
** returns 0 on failure
** needs to update old pwd because of cd -
*/
int	do_cd(char *path)
{
	if (!chdir(path))
		return (1);
	write(1, "cd: no such file or directory: ", 32);
	write(1, path, ft_strlen(path));
	write(1, "\n", 2);
	return (0);
}
