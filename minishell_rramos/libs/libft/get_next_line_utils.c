/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:00:11 by lprates           #+#    #+#             */
/*   Updated: 2021/09/25 16:05:06 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

static char	*loc_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (dest == src)
		return (dest);
	while (dest[j] != '\0')
		++j;
	while (src[i] != '\0')
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*join;

	if (!s1 && !s2)
		return (NULL);
	join = malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (!join)
		return (NULL);
	join[0] = 0;
	if (s1)
		loc_strcat(join, (char *)s1);
	if (s2)
		loc_strcat(join, (char *)s2);
	free((char *)s1);
	return (join);
}

int	has_line(char *keep)
{
	if (!keep)
		return (0);
	while (*keep)
	{
		if (*keep == '\n')
			return (1);
		keep++;
	}
	return (0);
}
