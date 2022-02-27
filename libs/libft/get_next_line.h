/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:00:07 by lprates           #+#    #+#             */
/*   Updated: 2021/09/25 16:03:53 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_params
{
	char	*buffer;
	int		reader;
}				t_params;

int				get_next_line(int fd, char **line);
unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size);
char			*gnl_strjoin(char const *s1, char const *s2);
void			ft_putstr(char *str);
char			*ft_strdup(char *src);
size_t			gnl_strlen(const char *str);
int				has_line(char *keep);
char			*join_str(char const *s1, char const *s2);

#endif
