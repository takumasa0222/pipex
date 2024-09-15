/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 04:16:52 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/09/15 21:41:05 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex.h"
#include "../libft/libft.h"
#include <fcntl.h>


void	init_pipex(int argc, char **argv, t_pipex **pipe_i)
{
	*pipe_i = malloc(1 * sizeof(t_pipex));
	if (!pipe_i)
		throw_err(*pipe_i, ENOMEM);
	(*pipe_i)->arg = NULL;
	(*pipe_i)->arg = set_arg(argc, argv);
	if (!(*pipe_i)->arg)
		throw_err(*pipe_i, ENOMEM);
	set_here_doc(*pipe_i);
	(*pipe_i)->cmd = NULL;
	(*pipe_i)->cmd = set_cmd(*pipe_i);
	if (!(*pipe_i)->cmd)
		throw_err(*pipe_i, ENOMEM);
	set_cmd_cnt(*pipe_i);
	(*pipe_i)->is_valid_infile = 1;
}

void	set_here_doc(t_pipex *pipe_i)
{
	if (!pipe_i)
		return ;
	if (!(ft_strncmp(pipe_i->arg[0], HERE_DOC, 8)))
		pipe_i->is_here_doc = 1;
	else
		pipe_i->is_here_doc = 0;
}

void	set_cmd_cnt(t_pipex *pipe_i)
{
	if (!pipe_i)
		return ;
	pipe_i->cmd_cnt = get_arry_size(pipe_i->cmd);
}

char	**set_arg(int argc, char **argv)
{
	char	**ret;
	int		i;

	i = 0;
	ret = malloc(argc * sizeof(char *));
	if (!ret)
		return (NULL);
	while (i < argc - 1)
	{
		ret[i] = ft_strdup(argv[i + 1]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

char	**set_cmd(t_pipex *pipe_i)
{
	char	**ret;
	int		i;
	int		arg_size;
	int		file_num;

	file_num = 2;
	if (pipe_i->is_here_doc)
		file_num = 3;
	arg_size = get_arry_size(pipe_i->arg) - file_num;
	ret = malloc((arg_size + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < arg_size)
	{
		ret[i] = ft_strdup(pipe_i->arg[i + file_num - 1]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
