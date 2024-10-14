/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 04:35:59 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/10/14 14:27:11 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex_bonus.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

int	pipex(t_pipex *pipe_i, char **cmd_path, char **envp)
{
	int	i;
	int	c_status;

	i = -1;
	while (++i < pipe_i->cmd_cnt)
		pipe_exec(pipe_i, i, cmd_path, envp);
	i = -1;
	if (!(pipe_i->is_valid_infile))
		i = 0;
	c_status = 0;
	while (++i < pipe_i->cmd_cnt)
		waitpid(pipe_i->fork_ids[i], &c_status, 0);
	if (WIFSIGNALED(c_status))
		return (WTERMSIG(c_status) + 128);
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
void	pipe_exec(t_pipex *pipe_i, int i, char **cmd_path, char **envp)
{
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		throw_err(pipe_i, 0);
	pipe_i->fork_ids[i] = fork();
	if (pipe_i->fork_ids[i] == 0)
	{
		child_process_fd_ctrl(pipe_i, p_fd, i);
		exec_cmd(pipe_i, i, cmd_path, envp);
	}
	else if (pipe_i->fork_ids[i] == -1)
	{
		close_fds(p_fd[0], p_fd[1]);
		throw_err(pipe_i, 0);
	}
	else
	{
		parent_process_fd_ctrl(pipe_i, p_fd);
	}
}

void	child_process_fd_ctrl(t_pipex *pipe_i, int *p_fd, int i)
{
	custom_dup2(pipe_i->in_fd, STDIN_FILENO, pipe_i, p_fd[1]);
	close(pipe_i->in_fd);
	custom_dup2(p_fd[1], STDOUT_FILENO, pipe_i, p_fd[0]);
	close_fds(p_fd[0], p_fd[1]);
	if (i == (get_arry_size(pipe_i->cmd) - 1))
		custom_dup2(pipe_i->out_fd, STDOUT_FILENO, pipe_i, -1);
	close(pipe_i->out_fd);
}

void	parent_process_fd_ctrl(t_pipex *pipe_i, int *p_fd)
{
	if (pipe_i->in_fd == -1)
	{
		close(p_fd[1]);
		pipe_i->in_fd = p_fd[0];
	}
	else
	{
		custom_dup2(p_fd[0], pipe_i->in_fd, pipe_i, p_fd[1]);
		close_fds(p_fd[0], p_fd[1]);
	}
}

void	exec_cmd(t_pipex *pipe_i, int i, char **cmd_path, char **envp)
{
	char	**cmd;
	int		ret;
	char	*exec_cmd;

	cmd = ft_cmd_tokenizer(pipe_i->cmd[i], ' ');
	if (!cmd)
		throw_err(pipe_i, BASH_GENERAL_ERR);
	cmd_exec_check(cmd, cmd_path, &exec_cmd, pipe_i);
	ret = execve(exec_cmd, cmd, envp);
	if (ret)
	{
		perror("");
		free(exec_cmd);
		multi_free_close(pipe_i, BASH_GENERAL_ERR, cmd);
	}
}
