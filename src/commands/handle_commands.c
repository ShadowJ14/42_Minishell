/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 22:05:21 by rramos            #+#    #+#             */
/*   Updated: 2022/04/24 23:14:34 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_len(t_cmd *cur)
{
	int			count;
	t_cmd	*tmp;

	count = 0;
	tmp = cur;
	while (tmp->exec)
	{
		count++;
		tmp++;
	}
	return (count);
}

int	redirect_file_in(t_cmd **cmd, t_cmd *cur, int chain)
{
	if (chain == REDIRECTI)
	{
		if ((*cmd)->pipe[0] != 0)
			close((*cmd)->pipe[0]);
		(*cmd)->pipe[0] = open(cur->exec, O_RDONLY);
		if ((*cmd)->pipe[0] == -1)
		{
			write(1, "minishell: ", 11);
			perror(cur->exec);
			return (-1);
		}
	}
	/*else if (chain == HEREDOC)
	{
		if ((*cmd)->pipe[0] != 0)
			close((*cmd)->pipe[0]);
		(*cmd)->pipe[0] = create_heredoc_fd(cmd, &cur);
		if ((*cmd)->pipe[0] == -1)
			return (-1);
	}*/
	return (0);
}

int	redirect_file_out(t_cmd **cmd, t_cmd *cur, int chain)
{
	if (chain == REDIRECTO)
	{
		if ((*cmd)->pipe[1] != 1)
			close((*cmd)->pipe[1]);
		(*cmd)->pipe[1] = open(cur->exec, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if ((*cmd)->pipe[1] == -1)
			return (-1);
	}
	else if (chain == APPEND)
	{
		if ((*cmd)->pipe[1] != 1)
			close((*cmd)->pipe[1]);
		(*cmd)->pipe[1] = open(cur->exec, O_CREAT | O_RDWR | O_APPEND, 0644);
		if ((*cmd)->pipe[1] == -1)
			return (-1);
	}
	return (0);
}

int	open_fd(t_cmd **cmd)
{
	t_cmd	*cur;

	cur = *cmd;
	if (cur->chain == REDIRECTI || cur->chain == HEREDOC)
		if (redirect_file_in(cmd, cur + 1, cur->chain) == -1)
			return (-1);
	if (cur->chain == REDIRECTO || cur->chain == APPEND)
		if (redirect_file_out(cmd, cur + 1, cur->chain) == -1)
			return (-1);
	return (0);
}

int	wait_pid(t_cmd **cmd, pid_t *pid)
{
	t_cmd	*cur;
	int			len;
	int			i;

	i = 0;
	cur = *cmd;
	len = cmd_len(cur);
	if (len == 1 && is_builtin(*cmd, NULL))
	{
		return (0);
	}
	while (i < len)
	{
		if (cur->chain == APPEND || cur->chain == REDIRECTO \
			|| cur->chain == REDIRECTI || cur->chain == HEREDOC)
		{
			cur++;
			i++;
		}
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
	printf("i value: %i\n", i);
	if (nfd[i] == NULL)
		return (50);
	if (pipe(nfd[i]) == -1)
		return (40);
	if (i == 0)
		//dup2(cur->pipe[0], 0);
		cur->pipe[0] = 0;
	else
		cur->pipe[0] = nfd[i - 1][0];
	if ((cur + 1)->exec == NULL)
	{
		close(nfd[i][0]);
		close(nfd[i][1]);
		cur->pipe[1] = 1;
		//dup2(cur->pipe[1], 1);
	}
	else
		cur->pipe[1] = nfd[i][1];
	return (0);
}

int	open_pipe(t_cmd **cmd)
{
	t_cmd	*cur;
	int			i;
	int			**nfd;
	int			ret;

	i = 0;
	cur = *cmd;
	nfd = malloc(sizeof(int *) * (cmd_len(cur) + 1));
	if (nfd == NULL)
		return (50);
	nfd[cmd_len(cur)] = NULL;
	while (cur->exec)
	{
		if (i != 0 && ((cur - 1)->chain == APPEND || (cur - 1)->chain == REDIRECTO \
			|| (cur - 1)->chain == REDIRECTI || (cur - 1)->chain == HEREDOC))
			;
		else
		{	
			ret = init_pipe(nfd, i, cur, *cmd);
			if (ret != 0)
			{
				//free_nfd(nfd);
				return (ret);
			}
			i++;
		}
		cur++;
	}
	//free_nfd(nfd);
	return (0);
}

//? should be return code
int	msh_execute(t_cmd *cmd, t_env_elem *env_linklist)
{
	pid_t	*pid;
	int		ret;

	pid = malloc(sizeof(pid_t) * cmd_len(cmd));
	if (pid == NULL)
		return (50);
	ret = open_pipe(&cmd);
	if (ret != 0)
		return (ret);
	if (pid == NULL)
		return (50);
	//int	return_code;

	//return_code = builtin(cmd, builtin_funcs, env_linklist);
	//if (!return_code)
	//exec_sysfunction(cmd, builtin_funcs, env_linklist);
	forking(cmd, pid, env_linklist);
	wait_pid(&cmd, pid);
	free(pid);
	return (0);
}

int	msh_execute_two(t_cmd *cmd, char **builtin_funcs, t_env_elem *env_linklist)
{
	int	return_code;

	(void) builtin_funcs;
	return_code = is_builtin(cmd, env_linklist);
	if (!return_code)
		return_code = exec_sysfunction_two(cmd, NULL);
	return (1);
}

int	exec_sysfunction_two(t_cmd *cmd, char **str)
{
	char	*exec;

	exec = check_sysfunction(cmd->exec);
	if (exec)
	{
		if (execve(exec, cmd->args, str) == -1)
		{
			perror("msh");
			exit(EXIT_FAILURE);
		}
		free(exec);
	}
	else
		printf("cmd '%s' not found.\n", cmd->exec);
	return (0);
}

void	close_fd_all(t_cmd **cmd)
{
	t_cmd	*cur;

	cur = *cmd;
	while (cur->exec)
	{
		if (cur->pipe[0] != 0)
			close(cur->pipe[0]);
		if (cur->pipe[1] != 1)
			close(cur->pipe[1]);
		cur++;
	}
}

int	ft_execve_fct(t_cmd **cmd, t_cmd **first, pid_t *pid, t_env_elem *env_linklist)
{
	char		**str;

	(void) pid;
	dup2((*cmd)->pipe[0], STDIN_FILENO);
	dup2((*cmd)->pipe[1], STDOUT_FILENO);
	close_fd_all(first);
	str = convert_linked_list_to_array(env_linklist);
	if (str == NULL)
		exit(42);
	if (is_builtin(*cmd, env_linklist))
		execute_builtins((*cmd)->exec, (*cmd)->args, env_linklist);
	else
		exec_sysfunction_two(*cmd, str);
		//ft_exec_cmd(cmd, first, str, pid);
	return (0);
}

int	multi_fork(pid_t *pid, int i, t_cmd **cmd, t_cmd **cur, t_env_elem *env_linklist)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid[i] = fork();
	if (pid[i] == -1)
		exit(1);
	if (pid[i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ft_execve_fct(cur, cmd, pid, env_linklist);
		exit (0);
	}
	if ((*cur)->pipe[0] != 0)
		close((*cur)->pipe[0]);
	if ((*cur)->pipe[1] != 1)
		close((*cur)->pipe[1]);
	return (0);
}

int	forking(t_cmd *cmd, pid_t *pid, t_env_elem *env_linklist)
{
	int		len;
	int		i;
	t_cmd	*cur;

	i = -1;
	cur = cmd;
	len = cmd_len(cur);
	printf("cmd_count: %i\n", len);
	while (cur->exec)
	{
		open_fd(&cur);
		if (cur->chain == APPEND || cur->chain == REDIRECTO \
			|| cur->chain == REDIRECTI || cur->chain == HEREDOC)
			cur++;
		cur++;
	}
	cur = cmd;
	if (len == 1 && is_builtin(cur, env_linklist))
	{
		execute_builtins(cmd->exec, cmd->args, env_linklist);
		return (1);
	}
	while (++i < len)
	{
		multi_fork(pid, i, &cmd, &cur, env_linklist);
		if (cur->chain == APPEND || cur->chain == REDIRECTO \
			|| cur->chain == REDIRECTI || cur->chain == HEREDOC)
		{
			cur++;
			i++;
		}
		cur++;
	}
	return (0);
}
