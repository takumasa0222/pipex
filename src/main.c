/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 03:04:18 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/10/06 04:26:18 by tamatsuu         ###   ########.fr       */
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
	init_pipex(argc, argv, &pipe_i, path);
	validate_args(pipe_i);
	ret = pipex(pipe_i, path);
	close_pipex(pipe_i, ret);
}
