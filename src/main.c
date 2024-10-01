/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 03:04:18 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/10/02 03:01:41 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipe_i;
	int		ret;
	char	**path;

	ret = 0;
	pipe_i = NULL;
	path = NULL;
	init_path(envp, &path);
	init_pipex(argc, argv, &pipe_i);
	validate_args(pipe_i);
	// for(int i = 0;path[i];i++)
	// {
	// 	printf("%s\n",path[i]);
	// }
	// printf("in_fd %d\n",pipe_i->in_fd);
	// printf("out_fd %d\n",pipe_i->out_fd);
	// printf("heredoc %d\n", pipe_i->is_here_doc);
	// printf("is_valid_infile %d\n", pipe_i->is_valid_infile);
	// printf("cmd_cnt %d\n", pipe_i->cmd_cnt);
	ret = pipex(pipe_i, path);
	close_pipex(pipe_i, ret);
}
