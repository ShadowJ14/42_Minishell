/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sysfuncs_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rramos <rramos@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:07:00 by lprates           #+#    #+#             */
/*   Updated: 2022/04/10 18:16:42 by rramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_error(int my_pipe[2], char *cmd, t_command *command)
{
	close(my_pipe[0]);
	dup2(my_pipe[1], 1);
	if (execve(cmd, command[0].args, NULL) == -1)
	{
		perror("msh");
		exit(EXIT_FAILURE);
	}
	close(my_pipe[1]);
}

/*
** funtions that handles the redirection in and append in to file
**
*/
static void	send_output(int pipe, char *path, int chain)
{
	char	*error_message;
	char	reading_buf[1];
	int		file;
	int		mode;

	if (chain == APPENDO)
		mode = O_RDWR | O_APPEND;
	else
		mode = O_RDWR | O_TRUNC;
	file = open(path, mode);
	if (file == -1)
		file = open(path, mode | O_CREAT, 0666);
	if (file == -1)
	{
		error_message = ft_strjoin("minishell: ", path);
		perror(error_message);
		free_memory((void **)error_message);
		return ;
	}
	while (read(pipe, reading_buf, 1) > 0)
	{
		write(file, reading_buf, 1);
	}
	close(file);
}

static char	*check_sysfunction(char *func)
{
	char	*envs;
	char	**ret;
	char	*cmd;
	int		ret_access;

	envs = getenv("PATH");
	ret = ft_split(envs, ':');
	while (*ret)
	{
		cmd = ft_strjoin(*ret, ft_strjoin("/", func));
		ret_access = access(cmd, X_OK);
		if (ret_access == 0)
		{
			return (cmd);
		}
		free(cmd);
		if (*ret)
			ret++;
	}
	return (NULL);
}

static void	do_fork(int pid, int my_pipe[2], t_command *command, \
	char **environment_array)
{
	char	*cmd;
	int		status;

	waitpid(pid, &status, WUNTRACED);
	while (!WIFEXITED(status) && !WIFSIGNALED(status))
		waitpid(pid, &status, WUNTRACED);
	close(my_pipe[1]);
	if (command[0].chain == APPENDO || command[0].chain == REDIRECTO)
		send_output(my_pipe[0], command[1].args[0], command[0].chain);
	else if (command[0].chain == PIPE)
	{
		cmd = check_sysfunction(command[1].command);
		dup2(my_pipe[0], 0);
		(void)environment_array;
		if (execve(cmd, command[1].args, NULL) == -1)
		{
			perror("msh");
			exit(EXIT_FAILURE);
		}
	}
	close(my_pipe[0]);
	ft_putstr("(debug) parent out pipe closing\n");
}

int	exec_sysfunction(t_command *command, char **environment_array)
{
	int		pid;
	char	*cmd;
	int		my_pipe[2];

	if (pipe(my_pipe) == -1)
		perror("Error creating pipe");
	cmd = check_sysfunction(command[0].command);
	if (cmd)
	{
		pid = fork();
		if (!pid)
			do_error(my_pipe, cmd, command);
		else if (pid < 0)
			perror("msh");
		else
			do_fork(pid, my_pipe, command, environment_array);
		free(cmd);
	}
	return (0);
}
