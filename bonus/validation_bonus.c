/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 01:45:59 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/10/06 18:29:57 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"
/*
考慮事項
・入力ファイルが存在しないとき エラー出力
・入出力ファイルへのR/W権限がない時 エラー出力
・コマンドの実行権限がない時 エラー出力
・コマンドが存在しないとき エラー出力
*/

void	validate_args(t_pipex *pipe_i)
{
	argnum_check(pipe_i);
	infile_check(pipe_i);
	outfile_check(pipe_i);
}

void	argnum_check(t_pipex *pipe_i)
{
	if (pipe_i->cmd_cnt < 2)
		throw_err(pipe_i, BASH_GENERAL_ERR);
}

/*
infile は存在しない場合、自動的に、エラーとなる。
権限の確認と、読み込みの確認が同時にできるのかについては確認が必要
outfile の場合、ファイルが存在する場合は、書き込み権限の有無の確認が必要。
ファイルが存在しない場合は作成する。
*/
void	infile_check(t_pipex *pipe_i)
{	
	char	*tmp_err;

	tmp_err = init_tmp_err(pipe_i, 0);
	if (pipe_i->is_here_doc)
	{
		init_here_doc(pipe_i);
		set_infile(pipe_i, HERE_DOC_TMP);
	}
	else if (access(pipe_i->arg[0], F_OK | R_OK) == 0)
		set_infile(pipe_i, pipe_i->arg[0]);
	else
	{
		pipe_i->is_valid_infile = 0;
		pipe_i->in_fd = -1;
		perror(tmp_err);
	}
	free(tmp_err);
}

void	outfile_check(t_pipex *pipe_i)
{	
	ssize_t	i;
	char	*tmp_err;

	i = get_arry_size(pipe_i->arg) - 1;
	tmp_err = init_tmp_err(pipe_i, i);
	if (access(pipe_i->arg[i], F_OK) != 0 \
	|| access(pipe_i->arg[i], F_OK | W_OK) == 0)
	{
		if (pipe_i->is_here_doc)
			set_outfile_append(pipe_i, pipe_i->arg[i]);
		else
			set_outfile(pipe_i, pipe_i->arg[i]);
	}
	else
	{	
		pipe_i->out_fd = -1;
		perror(tmp_err);
	}
	free(tmp_err);
}
