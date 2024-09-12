/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 03:04:18 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/09/12 01:02:08 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	t_pipex	*pipe_i;

	pipe_i = NULL;
	argc = argc + 0;
	init_pipex(argc, argv, &pipe_i);
	// validate_args(pipe_i);
	pipex(pipe_i);
	// close_pipex(pipe_i);
}
