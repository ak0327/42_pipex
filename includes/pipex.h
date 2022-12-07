/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 13:28:49 by takira            #+#    #+#             */
/*   Updated: 2022/12/04 13:28:50 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/errno.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>

# include "./../lib/libft/libft.h"
# include "./../lib/libftprintf/ft_printf.h"
# include "./../lib/libgnl/get_next_line.h"

# define SPACES	"\t\n\v\f\r "

# define READ	0
# define WRITE	1

typedef struct s_pipe	t_pipe;
struct s_pipe
{
	char	**env;
	char	**av;
	char	*cmd_path1;
	char	*cmd_path2;
	char	**input_cmd1;
	char	**input_cmd2;
	char	**env_paths;
	char	*infile;
	char	*outfile;
	pid_t	pid1;
	pid_t	pid2;
	int		pipe_fd[2];
	int		file_fd[2];
};

/* inputs.c */
void	get_env_paths(t_pipe *p, int fail_exit_no);
void	get_cmds_from_argv(t_pipe *p, int fail_exit_no);
void	get_file_names(t_pipe *p, int fail_exit_no);

/* fd.c */
void	set_file_fds(t_pipe *p, int fail_exit_no);
void	dup_fds(t_pipe *p, int fail_exit_no);

/* child.c */
void	make_pipe(t_pipe *p, int fail_exit_no);
void	child_for_cmd1(t_pipe *p, int fail_exit_no);
void	child_for_cmd2(t_pipe *p, int fail_exit_no);
void	wait_pids(t_pipe *p, int fail_exit_no);

/* utils.c */
void	errmsg_and_exit(char *errmsg, int exit_no);
void	perror_and_exit(char *err_str, int exit_no);
void	close_and_frees(t_pipe *p);

#endif
