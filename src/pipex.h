/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 03:13:58 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/09/10 02:49:54 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H



typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	int		is_here_doc;
	int		is_valid_infile;
	char	**cmd;
	int		cmd_cnt;
}	t_pipex;

int		main(int argc, char *argv[]);

void	init_pipex(int argc, char **argv, t_pipex **pipe_i);
void	set_here_doc(t_pipex *pipe_i);
void	set_cmd_cnt(t_pipex *pipe_i);
char	**set_cmd(int argc, char **argv);

void	pipex(t_pipex *pipe_i);
void	pipe_exec(t_pipex *pipe_i, int i);
void	exec_cmd(t_pipex *pipe_i, int i);

#endif