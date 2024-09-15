/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:44:58 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/09/15 23:00:02 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "../libft/libft.h"

void	set_infile(t_pipex *pipe_i)
{
	pipe_i->in_fd = open(pipe_i->arg[0], O_RDONLY, DEF_PERM);
}

void	set_outfile(t_pipex *pipe_i)
{
	int	i;

	i = get_arry_size(pipe_i->arg);
	pipe_i->out_fd = open(pipe_i->arg[i - 1], \
	O_RDWR | O_CREAT | O_TRUNC, DEF_PERM);
}

void	set_outfile_append(t_pipex *pipe_i)
{
	int	i;

	i = get_arry_size(pipe_i->cmd);
	pipe_i->out_fd = open(pipe_i->arg[i - 1], \
	O_RDWR | O_CREAT | O_APPEND, DEF_PERM);
}

char	*init_tmp_err(t_pipex *pipe_i, int x)
{
	char	*ret;
	int		i;
	ssize_t	file_name_len;

	ret = malloc(MSG_SIZE * sizeof(char *));
	if (!ret)
		throw_err(pipe_i, ENOMEM);
	i = 0;
	file_name_len = ft_strlen(pipe_i->arg[x]);
	while (i < file_name_len)
	{
		ret[i] = pipe_i->arg[x][i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
