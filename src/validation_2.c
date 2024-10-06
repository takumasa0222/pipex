/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:42:47 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/10/06 23:34:53 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"

void	cmd_executable_check(char **cmd, char **cmd_path, char **exec_cmd)
{
	int		exec_status;

	exec_status = 0;
	if (!cmd)
		throw_err(NULL, BASH_GENERAL_ERR);
	if (!check_cmd_exec(cmd[0], exec_cmd) || !cmd_path)
		exec_status = check_cmd_exec(cmd[0], exec_cmd);
	else if (ft_strchr(cmd[0], '/'))
		exec_status = check_cmd_exec(cmd[0], exec_cmd);
	else if (!cmd[0])
		exec_status = CMD_NOT_FOUND;
	else
		exec_status = check_cmd_exec_w_path(cmd_path, cmd[0], exec_cmd);
	if (exec_status == PERMISSION_DENIED)
	{
		ft_printerr(PERMISSION_DENIED_MSG, cmd[0]);
		exit(126);
	}
	else if (exec_status == CMD_NOT_FOUND)
	{
		ft_printerr(CMD_NOT_FOUND_MSG, cmd[0]);
		exit(127);
	}
}

int	check_cmd_exec(char *cmd, char **exec_cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
		{
			*exec_cmd = ft_strdup(cmd);
			return (0);
		}
		return (PERMISSION_DENIED);
	}
	*exec_cmd = NULL;
	return (CMD_NOT_FOUND);
}

int	check_cmd_exec_w_path(char **cmd_path, char *cmd, char **ex_cmd)
{
	int		i;
	int		exec_status;
	char	*tmp;
	char	*tmp2;

	i = 0;
	exec_status = CMD_NOT_FOUND;
	while (cmd_path[i])
	{
		tmp = ft_strjoin(cmd_path[i], "/");
		tmp2 = ft_strjoin(tmp, cmd);
		if (access(tmp2, F_OK) == 0)
		{
			if (access(tmp2, X_OK) == 0)
				return (*ex_cmd = ft_strdup(tmp2), free(tmp), free(tmp2), 0);
			exec_status = PERMISSION_DENIED;
		}
		i++;
		free(tmp);
		free(tmp2);
		tmp = NULL;
		tmp2 = NULL;
	}
	return (exec_status);
}

void	ft_printerr(char *err_msg, char *err_trg)
{
	if (!err_msg)
		return ;
	if (err_trg)
	{
		write(STDERR_FILENO, err_trg, ft_strlen(err_trg));
		write(STDERR_FILENO, COLON, ft_strlen(COLON));
	}
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
}
