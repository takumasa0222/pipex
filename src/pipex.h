/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 03:13:58 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/09/28 02:32:05 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define FD_NUM 4096
# define DEF_PERM 0644
# define MSG_SIZE 1024
# define BASH_FILE_ERR_MSG "bash: "
# define CMD_NOT_FOUND_MSG "command not found\n"
# define PERMISSION_DENIED_MSG "Permission denied\n"
# define COLON ": "
# define PERMISSION_DENIED 1
# define CMD_NOT_FOUND 2


# define HERE_DOC "here_doc"
# define HERE_DOC_TMP ".here_doc.tmp"
# include <sys/wait.h>
# include <errno.h>

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

int		main(int argc, char *argv[], char *envp[]);

void	init_pipex(int argc, char **argv, t_pipex **pipe_i);
void	set_here_doc(t_pipex *pipe_i);
void	set_cmd_cnt(t_pipex *pipe_i);
char	**set_cmd(t_pipex *pipe_i);
char	**set_arg(int argc, char **argv);

int		pipex(t_pipex *pipe_i, char **cmd_path);
void	pipe_exec(t_pipex *pipe_i, int i, char **cmd_path);
void	exec_cmd(t_pipex *pipe_i, int i, char **cmd_path);

int		get_arry_size(char **arry);
void	throw_err(t_pipex *pipe_i, int err_no);
void	free_pipe_info(t_pipex *pipe_i);
void	close_pipex(t_pipex *pipe_i, int close_status);

void	validate_args(t_pipex *pipe_i);
void	argnum_check(t_pipex *pipe_i);
void	infile_check(t_pipex *pipe_i);
void	outfile_check(t_pipex *pipe_i);

void	init_path(char **envp, char ***path_var);

void	cmd_executable_check(char **cmd, char **cmd_path);
int		check_cmd_exec_w_path(char **cmd_path, char *cmd);
void	ft_printerr(char *err_msg, char *err_cmd);
int		check_cmd_exec(char *cmd);

void	set_infile(t_pipex *pipe_i, char *file_path);
void	set_outfile(t_pipex *pipe_i, char *file_path);
void	set_outfile_append(t_pipex *pipe_i, char *file_path);
char	*init_tmp_err(t_pipex *pipe_i, int x);
void	init_here_doc(t_pipex *pipe_i);

int		custom_dup2(int fd, int fd2, t_pipex *pipe_i, int fd3);
int		close_fds(int fd, int fd2);
#endif