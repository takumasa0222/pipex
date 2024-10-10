/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 03:04:18 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/10/10 20:15:58 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
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
	ret = pipex(pipe_i, path, envp);
	close_pipex(pipe_i, ret);
}
