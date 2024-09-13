/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 04:35:59 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/09/14 04:28:29 by tamatsuu         ###   ########.fr       */
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
	pid_t	fork_ret;
	//int		p_fd[2];
	int		c_status;
	
	i = 0;
	if (pipe_i->is_here_doc)
		dup2(0,	STDIN_FILENO);
	else
		dup2(pipe_i->in_fd, STDIN_FILENO);
	printf("%d\n", pipe_i->in_fd);
	printf("%d\n", pipe_i->cmd_cnt);
	printf("%d\n", pipe_i->out_fd);

	while (i < pipe_i->cmd_cnt)
	{
		i++;
		fork_ret = fork();
		pipe_exec(pipe_i, i, fork_ret);
		//子プロセスは全体で一気に走らす。最終的に、親プロセスで待つといった順番が必要そう
		waitpid(fork_ret, &c_status, 0);
	}
	//if (dup2(pipe_i->out_fd, STDOUT_FILENO) == -1)
	//{
	//	perror("dup2 failed for output redirection");
	//	exit(1);
	//}
	//i++;
	//exec_cmd(pipe_i, i);


}
// this function simulate | behavior
void	pipe_exec(t_pipex *pipe_i, int i, pid_t fork_ret)
{
	//pid_t	fork_ret;
	int		p_fd[2];
	int		c_status;

	c_status = 0;
	if (pipe(p_fd) == -1)
			return ;//error handle
	//fork_ret = fork();
	if (fork_ret == 0)
	{
		close(p_fd[0]);
		dup2(p_fd[1], STDOUT_FILENO);
		if (i == 2)
			dup2(pipe_i->out_fd, STDOUT_FILENO);
		close(p_fd[1]);
		exec_cmd(pipe_i, i);
		exit(0);
	}
	else
	{
		//wait(&c_status);
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
