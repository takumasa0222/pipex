/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 04:35:59 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/09/15 19:54:22 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

void	pipex(t_pipex *pipe_i)
{
	int	i;
	int	c_status;

	if (pipe_i->is_here_doc)
		dup2(0, STDIN_FILENO);
	else
		dup2(pipe_i->in_fd, STDIN_FILENO);
	printf("in_fd %d\n",pipe_i->in_fd);
	printf("out_fd %d\n",pipe_i->out_fd);
	i = -1;
	if (!(pipe_i->is_valid_infile))
		i = 0;
	while (++i < pipe_i->cmd_cnt)
		pipe_exec(pipe_i, i);
	i = -1;
	if (!(pipe_i->is_valid_infile))
		i = 0;
	while (++i < 2)
		waitpid(pipe_i->fork_ids[i], &c_status, 0);
}

// this function simulate pipe behavior
void	pipe_exec(t_pipex *pipe_i, int i)
{
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		return ;//error handle
	pipe_i->fork_ids[i] = fork();
	if (pipe_i->fork_ids[i] == 0)
	{
		close(p_fd[0]);
		dup2(p_fd[1], STDOUT_FILENO);
		if (i == (get_arry_size(pipe_i->cmd) - 1))
			dup2(pipe_i->out_fd, STDOUT_FILENO);
		close(p_fd[1]);
		exec_cmd(pipe_i, i);
		exit(0);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], STDIN_FILENO);
		close(p_fd[0]);
	}
}

void	exec_cmd(t_pipex *pipe_i, int i)
{
	char	**cmd;

	cmd = ft_split(pipe_i->cmd[i], ' ');
	if (!cmd)
		return ;// error handle
	execvp(cmd[0], cmd);
	perror("execvp failed");
}
