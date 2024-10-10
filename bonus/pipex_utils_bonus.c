/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:59:42 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/10/10 20:35:57 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libft/libft.h"

int	get_arry_size(char **arry)
{
	int	ret;

	ret = 0;
	if (!arry)
		return (ret);
	while (arry[ret])
		ret++;
	return (ret);
}

void	throw_err(t_pipex *pipe_i, int err_num)
{
	char	*err_msg;

	err_msg = NULL;
	if (err_num)
	{
		err_msg = strerror(err_num);
		ft_putstr_fd(err_msg, STDERR_FILENO);
	}
	if (pipe_i)
	{
		close_fds(pipe_i->in_fd, pipe_i->out_fd);
		if (pipe_i->is_here_doc)
			unlink(HERE_DOC_TMP);
		free_path(pipe_i->path);
		free_pipe_info(pipe_i);
	}
	if (err_num)
		exit(err_num);
	exit(EXIT_FAILURE);
}

void	free_pipe_info(t_pipex *pipe_i)
{
	int	i;

	i = 0;
	if (!pipe_i)
		return ;
	while (pipe_i->arg[i])
	{
		free(pipe_i->arg[i]);
		pipe_i->arg[i] = NULL;
		i++;
	}
	i = 0;
	free(pipe_i->arg);
	while (pipe_i->cmd[i])
	{
		free(pipe_i->cmd[i]);
		pipe_i->cmd[i] = NULL;
		i++;
	}
	free(pipe_i->cmd);
	free(pipe_i);
}

void	free_path(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
}

void	close_pipex(t_pipex *pipe_i, int close_status)
{
	if (pipe_i->is_here_doc)
		unlink(HERE_DOC_TMP);
	close_fds(pipe_i->in_fd, pipe_i->out_fd);
	free_path(pipe_i->path);
	free_pipe_info(pipe_i);
	exit(close_status);
}
