/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 04:35:59 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/09/13 03:18:06 by tamatsuu         ###   ########.fr       */
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

	i = 0;
	if (pipe_i->is_here_doc)
		dup2(STDIN_FILENO, 0);
	else
		dup2(pipe_i->in_fd, STDIN_FILENO);
	printf("%d\n", pipe_i->in_fd);
	printf("%d\n", pipe_i->cmd_cnt);
	printf("%d\n", pipe_i->out_fd);
	while (i < pipe_i->cmd_cnt - 1)
	{
		i++;
		pipe_exec(pipe_i, i);
	}
	if (dup2(pipe_i->out_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed for output redirection");
		exit(1);
	}
	i++;
	exec_cmd(pipe_i, i);
}

// this function simulate | behavior
void	pipe_exec(t_pipex *pipe_i, int i)
{
	pid_t	fork_ret;
	int		p_fd[2];
	int		c_status;

	c_status = 0;
	if (pipe(p_fd) == -1)
		return ;//error handle
	fork_ret = fork();
//	if (fork_ret > 0)
	// error handle
	if (fork_ret == 0)
	{
		close(p_fd[0]);
		dup2(p_fd[1], STDOUT_FILENO);
		exec_cmd(pipe_i, i);
		close(p_fd[1]);
		exit(0);
	}
	else
	{
		wait(&c_status);
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
