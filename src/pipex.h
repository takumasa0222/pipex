/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 03:13:58 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/09/15 22:54:05 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define FD_NUM 4096
# define DEF_PERM 0644
# define MSG_SIZE 1024
# define BASH_FILE_ERR_MSG "bash: "

# define HERE_DOC "here_doc"
#include <sys/wait.h>
#include <errno.h>

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	int		is_here_doc;
	int		is_valid_infile;
	char	**arg;
	char	**cmd;
	int		cmd_cnt;
	pid_t	fork_ids[FD_NUM];
}	t_pipex;

int		main(int argc, char *argv[]);

void	init_pipex(int argc, char **argv, t_pipex **pipe_i);
void	set_here_doc(t_pipex *pipe_i);
void	set_cmd_cnt(t_pipex *pipe_i);
char	**set_cmd(t_pipex *pipe_i);
char	**set_arg(int argc, char **argv);

void	pipex(t_pipex *pipe_i);
void	pipe_exec(t_pipex *pipe_i, int i);
void	exec_cmd(t_pipex *pipe_i, int i);

int		get_arry_size(char **arry);
void	throw_err(t_pipex *pipe_i, int err_no);
void	free_pipe_info(t_pipex *pipe_i);

void	validate_args(t_pipex *pipe_i);
void	argnum_check(t_pipex *pipe_i);
void	infile_check(t_pipex *pipe_i);
void	outfile_check(t_pipex *pipe_i);


void	set_infile(t_pipex *pipe_i);
void	set_outfile(t_pipex *pipe_i);
void	set_outfile_append(t_pipex *pipe_i);
char	*init_tmp_err(t_pipex *pipe_i, int x);
#endif