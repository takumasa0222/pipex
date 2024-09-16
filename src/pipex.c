/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 04:35:59 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/09/16 23:33:58 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

int	pipex(t_pipex *pipe_i)
{
	int	i;
	int	c_status;

	if (pipe_i->is_valid_infile)
		custom_dup2(pipe_i->in_fd, STDIN_FILENO, pipe_i, -1);
	i = -1;
	if (!(pipe_i->is_valid_infile))
		i = 0;
	while (++i < pipe_i->cmd_cnt)
		pipe_exec(pipe_i, i);
	i = -1;
	if (!(pipe_i->is_valid_infile))
		i = 0;
	while (++i < pipe_i->cmd_cnt)
		waitpid(pipe_i->fork_ids[i], &c_status, 0);
	return (c_status);
}

// this function simulate pipe behavior
void	pipe_exec(t_pipex *pipe_i, int i)
{
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		throw_err(pipe_i, 0);
	pipe_i->fork_ids[i] = fork();
	if (pipe_i->fork_ids[i] == 0)
	{
		custom_dup2(p_fd[1], STDOUT_FILENO, pipe_i, p_fd[0]);
		close_fds(p_fd[0], p_fd[1]);
		if (i == (get_arry_size(pipe_i->cmd) - 1) && pipe_i->out_fd != -1)
			custom_dup2(pipe_i->out_fd, STDOUT_FILENO, pipe_i, -1);
		exec_cmd(pipe_i, i);
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

void	exec_cmd(t_pipex *pipe_i, int i)
{
	char	**cmd;

	cmd = ft_split(pipe_i->cmd[i], ' ');
	if (!cmd)
		throw_err(pipe_i, EINVAL);
	execvp(cmd[0], cmd);
	if (!(i == (get_arry_size(pipe_i->cmd) - 1) && pipe_i->out_fd == -1))
		perror("");
}
