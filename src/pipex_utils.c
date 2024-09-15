/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:59:42 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/09/15 23:34:04 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//void	clean_resource(t_pipex *pipe_i)
//{

//}

void	throw_err(t_pipex *pipe_i, int err_no)
{
	if (!err_no)
		strerror("");
	if (pipe_i)
		free_pipe_info(pipe_i);
	if (err_no)
		exit(err_no);
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
