/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 01:52:48 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/10/06 18:29:46 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../libft/libft.h"
#include <error.h>
#include <stdlib.h>

void	init_path(char **envp, char ***path_var)
{
	int		i;
	char	*tmp;

	if (!path_var)
		throw_err(NULL, BASH_GENERAL_ERR);
	if (!envp)
		return ;
	i = 0;
	tmp = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			tmp = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			*path_var = ft_split(tmp, ':');
			free(tmp);
			return ;
		}
		i++;
	}
}
