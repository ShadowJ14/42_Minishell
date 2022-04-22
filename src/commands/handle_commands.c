/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 22:05:21 by rramos            #+#    #+#             */
/*   Updated: 2022/04/13 00:50:27 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_len(t_command *cur)
{
	int	count;

	count = 0;
	while (cur->command)
	{
		count++;
		cur++;
	}
	return (count);
}

int	redirect_file_in(t_command **command, t_command *cur, int chain)
{
	if (chain == REDIRECTI)
	{
		if ((*command)->pipe[0] != 0)
			close((*command)->pipe[0]);
		(*command)->pipe[0] = open(cur->command, O_RDONLY);
		if ((*command)->pipe[0] == -1)
		{
			write(1, "minishell: ", 11);
			perror(cur->command);
			return (-1);
		}
	}
	/*else if (chain == HEREDOC)
	{
		if ((*command)->pipe[0] != 0)
			close((*command)->pipe[0]);
		(*command)->pipe[0] = create_heredoc_fd(command, &cur);
		if ((*command)->pipe[0] == -1)
			return (-1);
	}*/
	return (0);
}

int	redirect_file_out(t_command **command, t_command *cur, int chain)
{
	if (chain == REDIRECTO)
	{
		if ((*command)->pipe[1] != 1)
			close((*command)->pipe[1]);
		(*command)->pipe[1] = open(cur->command, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if ((*command)->pipe[1] == -1)
			return (-1);
	}
	else if (chain == APPEND)
	{
		if ((*command)->pipe[1] != 1)
			close((*command)->pipe[1]);
		(*command)->pipe[1] = open(cur->command, O_CREAT | O_RDWR | O_APPEND, 0644);
		if ((*command)->pipe[1] == -1)
			return (-1);
	}
	return (0);
}

int	open_fd(t_command **command)
{
	t_command	*cur;

	cur = *command;
	if (cur->chain == REDIRECTI || cur->chain == HEREDOC)
		if (redirect_file_in(command, cur + 1, cur->chain) == -1)
			return (-1);
	if (cur->chain == REDIRECTO || cur->chain == APPEND)
		if (redirect_file_out(command, cur + 1, cur->chain) == -1)
			return (-1);
	return (0);
}

int	wait_pid(t_command **command, pid_t *pid)
{
	t_command	*cur;
	int			len;
	int			i;

	i = 0;
	cur = *command;
	len = command_len(cur);
	if (len == 1 && is_builtin(*command, NULL))
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

int	init_pipe(int **nfd, int i, t_command *cur, t_command *command)
{
	(void) command;
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
	if ((cur + 1)->command == NULL)
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

int	open_pipe(t_command **command)
{
	t_command	*cur;
	int			i;
	int			**nfd;
	int			ret;

	i = 0;
	cur = *command;
	nfd = malloc(sizeof(int *) * (command_len(cur) + 1));
	if (nfd == NULL)
		return (50);
	nfd[command_len(cur)] = NULL;
	while (cur->command)
	{
		if (i != 0 && ((cur - 1)->chain == APPEND || (cur - 1)->chain == REDIRECTO \
			|| (cur - 1)->chain == REDIRECTI || (cur - 1)->chain == HEREDOC))
			;
		else
		{	
			ret = init_pipe(nfd, i, cur, *command);
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
int	msh_execute(t_command *command, t_environment_element *environment_linked_list)
{
	pid_t	*pid;
	int		ret;

	pid = malloc(sizeof(pid_t) * command_len(command));
	if (pid == NULL)
		return (50);
	ret = open_pipe(&command);
	if (ret != 0)
		return (ret);
	if (pid == NULL)
		return (50);
	//int	return_code;

	//return_code = builtin(command, builtin_funcs, environment_linked_list);
	//if (!return_code)
	//exec_sysfunction(command, builtin_funcs, environment_linked_list);
	forking(command, pid, environment_linked_list);
	wait_pid(&command, pid);
	free(pid);
	return (0);
}

int	msh_execute_two(t_command *command, char **builtin_funcs, t_environment_element *environment_linked_list)
{
	int	return_code;

	(void) builtin_funcs;
	return_code = is_builtin(command, environment_linked_list);
	if (!return_code)
		return_code = exec_sysfunction_two(command, NULL);
	return (1);
}

int	exec_sysfunction_two(t_command *command, char **str)
{
	char	*cmd;

	cmd = check_sysfunction(command->command);
	if (cmd)
	{
		if (execve(cmd, command->args, str) == -1)
		{
			perror("msh");
			exit(EXIT_FAILURE);
		}
		free(cmd);
	}
	else
		printf("Command '%s' not found.\n", command->command);
	return (0);
}

void	close_fd_all(t_command **command)
{
	t_command	*cur;

	cur = *command;
	while (cur->command)
	{
		if (cur->pipe[0] != 0)
			close(cur->pipe[0]);
		if (cur->pipe[1] != 1)
			close(cur->pipe[1]);
		cur++;
	}
}

int	ft_execve_fct(t_command **command, t_command **first, pid_t *pid, t_environment_element *environment_linked_list)
{
	char		**str;

	(void) pid;
	dup2((*command)->pipe[0], STDIN_FILENO);
	dup2((*command)->pipe[1], STDOUT_FILENO);
	close_fd_all(first);
	str = convert_linked_list_to_array(environment_linked_list);
	if (str == NULL)
		exit(42);
	if (is_builtin(*command, environment_linked_list))
		execute_builtins((*command)->command, (*command)->args, environment_linked_list);
	else
		exec_sysfunction_two(*command, str);
		//ft_exec_cmd(command, first, str, pid);
	return (0);
}

int	multi_fork(pid_t *pid, int i, t_command **command, t_command **cur, t_environment_element *environment_linked_list)
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
		ft_execve_fct(cur, command, pid, environment_linked_list);
		exit (0);
	}
	if ((*cur)->pipe[0] != 0)
		close((*cur)->pipe[0]);
	if ((*cur)->pipe[1] != 1)
		close((*cur)->pipe[1]);
	return (0);
}

int	forking(t_command *command, pid_t *pid, t_environment_element *environment_linked_list)
{
	int				len;
	int				i;
	t_command		*cur;

	i = -1;
	cur = command;
	len = command_len(cur);
	printf("command_count: %i\n", len);
	while (cur->command)
	{
		open_fd(&cur);
		if (cur->chain == APPEND || cur->chain == REDIRECTO \
			|| cur->chain == REDIRECTI || cur->chain == HEREDOC)
			cur++;
		cur++;
	}
	cur = command;
	if (len == 1 && is_builtin(cur, environment_linked_list))
	{
		execute_builtins(command->command, command->args, environment_linked_list);
		return (1);
	}
	while (++i < len)
	{
		multi_fork(pid, i, &command, &cur, environment_linked_list);
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
