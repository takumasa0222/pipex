/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:42:47 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/09/24 05:01:37 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"

void	cmd_executable_check(char **cmd, char **cmd_path)
{
	int		i;
	int		is_not_exec;
	char	*temp;
	char	*temp2;

	if (!cmd)
		throw_err(NULL, EINVAL);
	if (!cmd_path)
	{
		if (access(cmd[0], F_OK) == 0)
		{
			if (access(cmd[0], X_OK) == 0)
				return ;
			is_not_exec = 1;
		}
	}
	i = 0;
	is_not_exec = 0;
	while (cmd_path[i])
	{
		temp = ft_strjoin(cmd_path[i], "/");
		temp2 = ft_strjoin(temp, cmd[0]);
		if (access(temp2, F_OK) == 0)
		{
			if (access(temp2, X_OK) == 0)
			{
				free(temp);
				free(temp2);
				return ;
			}
			is_not_exec = 1;
		}
			return ;
		i++;
		free(temp);
		free(temp2);
	}
	if (is_not_exec)
		exit(126);
	exit(127);
}

int	is_cmd_exec(char *cmd)
{
	
}
