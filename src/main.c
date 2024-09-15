/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 03:04:18 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/09/15 19:16:19 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	t_pipex	*pipe_i;

	pipe_i = NULL;
	init_pipex(argc, argv, &pipe_i);
	validate_args(pipe_i);
	pipex(pipe_i);
	// close_pipex(pipe_i);
}
