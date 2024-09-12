/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 04:16:52 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/09/12 01:01:56 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex.h"
#include "../libft/libft.h"
#include <fcntl.h>
// #include <errno.h>

void	init_pipex(int argc, char **argv, t_pipex **pipe_i)
{
	*pipe_i = malloc(1 * sizeof(t_pipex));
	if (!pipe_i)
		exit(EXIT_FAILURE);// need to consider set error code and so on.
	(*pipe_i)->cmd = set_cmd(argc, argv);
	if (!(*pipe_i)->cmd)
		return ; // need to error handle
	set_here_doc(*pipe_i);
	if (!(*pipe_i)->cmd)
	{
		free(pipe_i); exit(EXIT_FAILURE); return;
	}
	set_cmd_cnt(*pipe_i);
	(*pipe_i)->out_fd = open((*pipe_i)->cmd[3], O_WRONLY);
	(*pipe_i)->in_fd = open((*pipe_i)->cmd[0], O_RDONLY);
}

void	set_here_doc(t_pipex *pipe_i)
{
	if (!pipe_i)
		return ;
	pipe_i->is_here_doc = 0;
}

void	set_cmd_cnt(t_pipex *pipe_i)
{
	int	i;

	if (!pipe_i)
		return ;
	i = 0;
	while (pipe_i->cmd[i])
		i++;
	if (pipe_i->is_here_doc)
		i = i - 3;
	else
		i = i - 2;
	pipe_i->cmd_cnt = i;
}

char	**set_cmd(int argc, char **argv)
{
	char	**ret;
	int		i;

	ret = malloc(argc * sizeof(char *));
	if (!ret)
		return (NULL); // need error handle
	while (i < argc - 1)
	{
		ret[i] = ft_strdup(argv[i + 1]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
