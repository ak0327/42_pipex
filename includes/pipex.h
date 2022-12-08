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

# define PATH_CURRENT	"./"

typedef struct s_pipe	t_pipe;
struct s_pipe
{
	// av, env
	char	**av;
	char	**env;
	char	**env_paths; // TODO: free; split
	// cmd
	char	**input_cmd1; // TODO: free; split
	char	**input_cmd2; // TODO: free; split
	char	*path_cmd1; // TODO: free; malloc
	char	*path_cmd2; // TODO: free; malloc
	bool	is_cmd1_relative;
	bool	is_cmd2_relative;
	// file
	char	*infile_name; // TODO: free; trim
	char	*outfile_name; // TODO: free; trim
	// pipe
	pid_t	pid1;
	pid_t	pid2;
	int		pipe_fd[2];
	int		file_fd[2];
	int		exit_status;
};

/* inputs.c */
void	get_inputs(t_pipe *p, int exit_no_if_fail);

/* fd.c */
void	open_infile(t_pipe *p, int exit_no_if_fail);
void	open_outfile(t_pipe *p, int exit_no_if_fail);

/* pipe.c */
void	exec_pipe(t_pipe *p, int exit_no_if_fail);

/* utils.c */
void	errmsg_str1_str2_exit(char *str1, char *str2, int exit_no);

void	perror_and_exit(char *err_str, int exit_no);
void	free_allocs(t_pipe *p);
void	free_and_ret_null(char **alloc_str);

/* for debug */
//void	fprint_2d_arr(char **array, char *info_str, FILE *fp);
//void	print_2d_arr(char **array, char *info_str);
//void	debug_msg_str1_n_str2_nl(char *str1, int n, char *str2);

#endif
