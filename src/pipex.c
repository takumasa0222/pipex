/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 04:35:59 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/10/06 02:50:54 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

int	pipex(t_pipex *pipe_i, char **cmd_path)
{
	int	i;
	int	c_status;

	i = -1;
	while (++i < pipe_i->cmd_cnt)
		pipe_exec(pipe_i, i, cmd_path);
	i = -1;
	if (!(pipe_i->is_valid_infile))
		i = 0;
	c_status = 0;
	while (++i < pipe_i->cmd_cnt)
		waitpid(pipe_i->fork_ids[i], &c_status, 0);
	return (WEXITSTATUS(c_status));
}

// this function simulate pipe behavior
/*
this function call pipe and create 2 file descriptor 
to communicate between processes.
Child process executes command.
in any case, pipe file descriptor should be closed until function reach to end.
9/18: all dup should be executed in here 
and need to consider which timing throwing error
*/
void	pipe_exec(t_pipex *pipe_i, int i, char **cmd_path)
{
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		throw_err(pipe_i, 0);
	pipe_i->fork_ids[i] = fork();
	if (pipe_i->fork_ids[i] == 0)
	{
		if (i == 0)
			custom_dup2(pipe_i->in_fd, STDIN_FILENO, pipe_i, p_fd[1]);
		custom_dup2(p_fd[1], STDOUT_FILENO, pipe_i, p_fd[0]);
		close_fds(p_fd[0], p_fd[1]);
		if (i == (get_arry_size(pipe_i->cmd) - 1))
			custom_dup2(pipe_i->out_fd, STDOUT_FILENO, pipe_i, -1);
		exec_cmd(pipe_i, i, cmd_path);
	}
	else if (pipe_i->fork_ids[i] == -1)
	{
		close_fds(p_fd[0], p_fd[1]);
		throw_err(pipe_i, 0);
	}
	else
	{
		custom_dup2(p_fd[0], STDIN_FILENO, pipe_i, p_fd[1]);
		close_fds(p_fd[0], p_fd[1]);
	}
}

void	exec_cmd(t_pipex *pipe_i, int i, char **cmd_path)
{
	char	**cmd;

	cmd = ft_cmd_tokenizer(pipe_i->cmd[i], ' ');
	if (!cmd)
		throw_err(pipe_i, EINVAL);
	cmd_executable_check(cmd, cmd_path);
	execvp(cmd[0], cmd);
	perror("");
	free(cmd);
}
