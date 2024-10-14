/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:42:47 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/10/14 14:11:52 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"

void	cmd_exec_check(char **cmd, char **path, char **exe_cmd, t_pipex *p_i)
{
	int		exec_status;

	exec_status = 0;
	if (!cmd)
		throw_err(NULL, BASH_GENERAL_ERR);
	if (!check_cmd_exec(cmd[0], exe_cmd) || !path)
		exec_status = check_cmd_exec(cmd[0], exe_cmd);
	else if (ft_strchr(cmd[0], '/'))
		exec_status = check_cmd_exec(cmd[0], exe_cmd);
	else if (!cmd[0])
		exec_status = CMD_NOT_FOUND;
	else
		exec_status = check_cmd_exec_w_path(path, cmd[0], exe_cmd);
	if (exec_status == PERMISSION_DENIED)
	{
		ft_printerr(PERMISSION_DENIED_MSG, cmd[0]);
		multi_free_close(p_i, 126, cmd);
	}
	else if (exec_status == CMD_NOT_FOUND)
	{
		ft_printerr(CMD_NOT_FOUND_MSG, cmd[0]);
		multi_free_close(p_i, 127, cmd);
	}
}

int	check_cmd_exec(char *cmd, char **exec_cmd)
{
	if (!cmd)
		return (CMD_NOT_FOUND);
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
