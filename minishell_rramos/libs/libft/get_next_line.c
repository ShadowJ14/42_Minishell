/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:59:26 by lprates           #+#    #+#             */
/*   Updated: 2021/09/25 16:03:08 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*trim_keep(char *keep)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!keep)
		return (0);
	while (keep[i] && keep[i] != '\n')
		i++;
	if (!keep[i])
	{
		free(keep);
		return (0);
	}
	tmp = malloc(sizeof(char) * ((gnl_strlen(keep) - i) + 1));
	if (!tmp)
		return (0);
	i++;
	while (keep[i])
		tmp[j++] = keep[i++];
	tmp[j] = '\0';
	free(keep);
	return (tmp);
}

char	*check_keep(char *keep)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!keep)
		return (0);
	while (keep[i] && keep[i] != '\n')
		i++;
	tmp = malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (0);
	i = 0;
	while (keep[i] && keep[i] != '\n')
	{
		tmp[i] = keep[i];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}

int	get_next_line(int fd, char **line)
{
	static char		*keep[1024];
	t_params		params;

	params.reader = 1;
	if ((read(fd, 0, 0) == -1) || !line || BUFFER_SIZE <= 0)
		return (-1);
	params.buffer = malloc(BUFFER_SIZE + 1);
	if (!params.buffer)
		return (-1);
	while (!has_line(keep[fd]) && params.reader != 0)
	{
		params.reader = read(fd, params.buffer, BUFFER_SIZE);
		if (params.reader == -1)
			break ;
		params.buffer[params.reader] = 0;
		keep[fd] = gnl_strjoin(keep[fd], params.buffer);
	}
	free(params.buffer);
	if (params.reader == -1)
		return (-1);
	*line = check_keep(keep[fd]);
	keep[fd] = trim_keep(keep[fd]);
	if (params.reader == 0)
		return (0);
	return (1);
}
