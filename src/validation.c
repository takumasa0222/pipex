/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 01:45:59 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/09/13 04:27:33 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>

/*
考慮事項
・入力ファイルが存在しないとき エラー出力
・入出力ファイルへのR/W権限がない時 エラー出力
・コマンドの実行権限がない時 エラー出力
・コマンドが存在しないとき エラー出力
*/

validate_args(t_pipex *pipe_i)
{
	argnum_check(pipe_i);
	file_check(pipe_i);
}

void	argnum_check(t_pipex *pipe_i)
{
	if (pipe_i->cmd_cnt < 2)
		return ;// error handle
}

void	file_check(t_pipex *pipe_i)
{	
	ssize_t	i;

	i = arg_len();
	if (pipe_i->is_here_doc)
		init_here_doc(pipe_i);
	else if (access(pipe_i->cmd[0], F_OK | R_OK) == 0)
		set_infile(pipe_i);
	else
		perror("bash");
/*
outfile の場合、ファイルが存在する場合は、書き込み権限の有無の確認が必要。
ファイルが存在しない場合は作成する。
*/
	if (access(pipe_i->cmd[i], F_OK) != 0 \
	|| access(pipe_i->cmd[i], F_OK | W_OK) == 0 )
	{
		if (pipe_i->is_here_doc)
			set_outfile_append(pipe_i);
		set_outfile(pipe_i);
	}
	else
		perror("bash");
}
