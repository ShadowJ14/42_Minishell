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

int	msh_execute(t_cmd *cmd)
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
	forking(cmd, pid);
	wait_pid(&cmd, pid);
	free(pid);
	handle_signals();
	return (0);
}

int	exec_sysfunction_two(t_cmd *cmd, t_cmd **first, char **str, pid_t *pid)
{
	char	*exec;

	(void) first;
	if (!cmd->args[0])
		return (0);
	exec = check_sysfunction(cmd->args[0]);
	if (exec)
	{
		if (execve(exec, cmd->args, str) == -1)
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
		free(exec);
		free_all(NULL);
		free(str);
		free(pid);
	}
	else
	{
		printf("minishell: %s: command not found.\n", cmd->args[0]);
		return (set_error_return(127, 127));
	}
	return (0);
}

int	ft_execve_fct(t_cmd **cmd, t_cmd **first, pid_t *pid)
{
	char		**str;
	t_env_elem	*env_linklist;

	env_linklist = env_singleton(NULL);
	dup2((*cmd)->pipe[0], STDIN_FILENO);
	dup2((*cmd)->pipe[1], STDOUT_FILENO);
	close_fd_all(first);
	str = convert_linked_list_to_array(env_linklist);
	if (str == NULL)
		exit(42);
	if (is_builtin(*cmd))
		execute_builtins(*cmd, pid, 1);
	else
		exec_sysfunction_two(*cmd, first, str, pid);
	free_env_llist(env_linklist);
	free_array((void **)str);
	return (g_exit_code);
}

int	multi_fork(pid_t *pid, int i, t_cmd **cmd, t_cmd **cur)
{
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, SIG_IGN);
	pid[i] = fork();
	if (pid[i] == -1)
		exit(1);
	if (pid[i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exit (ft_execve_fct(cur, cmd, pid));
	}
	if ((*cur)->pipe[0] != 0)
		close((*cur)->pipe[0]);
	if ((*cur)->pipe[1] != 1)
		close((*cur)->pipe[1]);
	return (0);
}

int	forking(t_cmd *cmd, pid_t *pid)
{
	int		len;
	int		i;
	t_cmd	*cur;

	i = -1;
	cur = cmd;
	len = cmd_len(cur);
	while (cur->exec)
	{
		open_fd(cur);
		cur++;
	}
	cur = cmd;
	if (len == 1 && is_builtin(cur))
	{
		execute_builtins(cmd, pid, cmd->pipe[1]);
		return (1);
	}
	while (++i < len)
	{
		multi_fork(pid, i, &cmd, &cur);
		cur++;
	}
	return (0);
}
