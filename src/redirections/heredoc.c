/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:09:20 by lprates           #+#    #+#             */
/*   Updated: 2022/05/22 18:12:48 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*int	random_char(void)
{
	char	buff[4];
	int		nbr;
	int		fd;

	fd = open("/dev/random", O_RDONLY);
	if (fd < -1)
		return (-1);
	read(fd, buff, 4);
	nbr = *(int *)buff;
	if (nbr < 0)
		nbr++;
	if (nbr < 0)
		nbr = nbr * (-1);
	return ('a' + nbr % 26);
}

char	*create_random_name(void)
{
	char	*name_file;
	int		i;

	i = 0;
	name_file = malloc(sizeof(char) * 11);
	name_file[10] = '\0';
	while (i < 10)
	{
		name_file[i] = (char)random_char();
		i++;
	}
	return (name_file);
}

int	write_in_fd(int fd, char *limitor, bool expanded)
{
	char	*str;

	while (1)
	{
		str = readline(">");
		if (str == NULL)
			return (45);
		if (ft_strcmp(limitor, str) == 1)
			break ;
		if (str[0] != '\0')
		{
			if (expanded == 0)
			{
				str = expanded_str(str);
				if (str == NULL)
					return (50);
			}
		}
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	free(str);
	return (0);
}

int	create_heredoc_fd(t_cmd **cmdl, t_token **cur)
{
	int		fd;
	char	*name_file;

	name_file = NULL;
	fd = -1;
	while (fd == -1)
	{
		if (name_file)
			free(name_file);
		name_file = creat_aleatori_name();
		fd = open(name_file, O_CREAT | O_EXCL | O_RDWR, 0644);
	}
	write_in_fd(fd, (*cur)->str, (*cur)->expanded);
	fd = open(name_file, O_RDONLY);
	(*cmdl)->fd_in = fd;
	if ((*cmdl)->name_file != NULL)
	{
		unlink((*cmdl)->name_file);
		free((*cmdl)->name_file);
	}
	(*cmdl)->name_file = name_file;
	return (fd);
}
*/
