/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:57:54 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/09/16 16:15:40 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

int	custom_dup2(int fd, int fd2, t_pipex *pipe_i, int fd3)
{
	int	ret;

	ret = dup2(fd, fd2);
	if (ret == -1)
	{
		close_fds(fd, fd3);
		throw_err(pipe_i, 0);
	}
	return (ret);
}

int	close_fds(int fd, int fd2)
{
	if (fd != -1)
		close(fd);
	if (fd2 != -1)
		close(fd2);
	return (0);
}
