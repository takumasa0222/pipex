/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:44:58 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/10/06 04:23:51 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "../libft/libft.h"
#include "../ft_get_next_line/get_next_line.h"

void	set_infile(t_pipex *pipe_i, char *file_path)
{
	pipe_i->in_fd = open(file_path, O_RDONLY, DEF_PERM);
	if (pipe_i->in_fd == -1)
		perror("");
}

void	set_outfile(t_pipex *pipe_i, char *file_path)
{
	pipe_i->out_fd = open(file_path, \
	O_WRONLY | O_CREAT | O_TRUNC, DEF_PERM);
	if (pipe_i->out_fd == -1)
		perror("");
}

void	set_outfile_append(t_pipex *pipe_i, char *file_path)
{
	pipe_i->out_fd = open(file_path, \
	O_WRONLY | O_CREAT | O_APPEND, DEF_PERM);
	if (pipe_i->out_fd == -1)
		perror("");
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

void	init_here_doc(t_pipex *pipe_i)
{
	int		tmp_fd;
	char	*line;

	tmp_fd = open(HERE_DOC_TMP, O_WRONLY | O_CREAT | O_TRUNC, DEF_PERM);
	if (tmp_fd == -1)
		throw_err(pipe_i, 0);
	line = NULL;
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		else if (ft_strlen(line) - 1 == ft_strlen(pipe_i->arg[1]) \
		&& !(ft_strncmp(line, pipe_i->arg[1], ft_strlen(line) - 1)))
			break ;
		else
			ft_putstr_fd(line, tmp_fd);
		free(line);
		line = NULL;
	}
	free(line);
	close(tmp_fd);
}
