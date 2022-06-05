/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:09:20 by lprates           #+#    #+#             */
/*   Updated: 2022/05/22 21:48:06 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*if_no_env(char *str, char *s1, int *cur)
{
	char	*new;
	char	*join;
	int		start;

	start = *cur;
	while (str[*cur] && str[*cur] != '$')
		(*cur)++;
	new = malloc(sizeof(char) * ((*cur) - start) + 1);
	if (new == NULL)
		return (free_str_ret_null(s1));
	new = ft_strncpy(new, str + start, ((*cur) - start));
	if (s1)
		join = ft_strjoin(s1, new);
	else
		join = ft_strjoin("", new);
	free_both(s1, new);
	return (join);
}

static char	*if_env(char *str, char *s1, int *cur)
{
	char	*env;
	char	*join;

	env = string_env(str, s1, cur);
	if (env == NULL)
		return (free_str_ret_null(s1));
	join = ft_strjoin(s1, env);
	free_both(s1, env);
	return (join);
}

static char	*expanded_str(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			new = if_env(str, new, &i);
			if (new == NULL)
				return (NULL);
		}
		else
		{
			new = if_no_env(str, new, &i);
			if (new == NULL)
				return (NULL);
		}
	}
	free(str);
	return (new);
}

int	write_in_fd(int fd, char *limitor, int not_expanded)
{
	char	*str;

	while (1)
	{
		str = readline(">");
		if (str == NULL)
			return (45);
		if (ft_strcmp(limitor, str) == 0)
			break ;
		if (str[0] != '\0')
		{
			if (!not_expanded)
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

int	create_heredoc_fd(t_cmd *cmd)
{
	int		fd;
	char	*name_file;

	name_file = NULL;
	fd = -1;
	while (fd == -1)
	{
		if (name_file)
			free(name_file);
		name_file = create_random_name();
		fd = open(name_file, O_CREAT | O_EXCL | O_RDWR, 0644);
	}
	write_in_fd(fd, cmd->file, cmd->no_expand);
	fd = open(name_file, O_RDONLY);
	cmd->pipe[0] = fd;
	cmd->file_name = name_file;
	if (cmd->file_name != NULL)
		unlink(cmd->file_name);
	return (fd);
}
