/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_and_pipes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 23:41:39 by lprates           #+#    #+#             */
/*   Updated: 2022/06/02 00:08:23 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_file_in(t_cmd *cmd, int chain)
{
	if (chain == REDIRECTI)
	{
		if (cmd->pipe[0] != 0)
			close(cmd->pipe[0]);
		cmd->pipe[0] = open(cmd->file, O_RDONLY);
		if (cmd->pipe[0] == -1)
		{
			perror("minishell");
			return (-1);
		}
	}
	else if (chain == HEREDOC)
	{
		if (cmd->pipe[0] != 0)
			close(cmd->pipe[0]);
		cmd->pipe[0] = create_heredoc_fd(cmd);
		if (cmd->pipe[0] == -1)
			return (-1);
	}
	return (0);
}

int	redirect_file_out(t_cmd *cmd, int chain)
{
	if (chain == REDIRECTO)
	{
		if (cmd->pipe[1] != 1)
			close(cmd->pipe[1]);
		cmd->pipe[1] = open(cmd->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (cmd->pipe[1] == -1)
			return (-1);
	}
	else if (chain == APPEND)
	{
		if (cmd->pipe[1] != 1)
		{
			close(cmd->pipe[1]);
		}
		cmd->pipe[1] = open(cmd->file, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (cmd->pipe[1] == -1)
			return (-1);
	}
	return (0);
}

int	wait_pid(t_cmd **cmd, pid_t *pid)
{
	t_cmd	*cur;
	int		len;
	int		i;

	i = 0;
	cur = *cmd;
	len = cmd_len(cur);
	if (len == 1 && is_builtin(*cmd))
	{
		return (0);
	}
	while (i < len)
	{
		waitpid(pid[i], &g_exit_code, 0);
		if (WIFEXITED(g_exit_code))
			g_exit_code = WEXITSTATUS(g_exit_code);
		else if (WIFSIGNALED(g_exit_code))
			g_exit_code = 128 + WTERMSIG(g_exit_code);
		i++;
		cur++;
	}
	return (0);
}

int	init_pipe(int **nfd, int i, t_cmd *cur, t_cmd *cmd)
{
	(void) cmd;
	nfd[i] = malloc(sizeof(int) * (2));
	if (nfd[i] == NULL)
		return (50);
	if (pipe(nfd[i]) == -1)
		return (40);
	if (i == 0)
		cur->pipe[0] = 0;
	else
		cur->pipe[0] = nfd[i - 1][0];
	if ((cur + 1)->exec == 0)
	{
		close(nfd[i][0]);
		close(nfd[i][1]);
		cur->pipe[1] = 1;
	}
	else
		cur->pipe[1] = nfd[i][1];
	return (0);
}

int	open_pipe(t_cmd **cmd)
{
	t_cmd	*cur;
	int		i;
	int		**nfd;
	int		ret;

	i = 0;
	cur = *cmd;
	nfd = malloc(sizeof(int *) * (cmd_len(cur) + 1));
	if (nfd == NULL)
		return (50);
	nfd[cmd_len(cur)] = NULL;
	while (cur->exec)
	{
		ret = init_pipe(nfd, i, cur, *cmd);
		if (ret != 0)
		{
			free(nfd);
			return (ret);
		}
		i++;
		cur++;
	}
	free_array((void **)nfd);
	free(nfd);
	return (0);
}
