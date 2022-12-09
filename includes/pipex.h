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

# define SPACES			"\t\n\v\f\r "
# define TRIM_CHARS		"\t\n\v\f\r '"

# define PATH_RELATIVE	"./"
# define PATH_ABSOLUTE	"/"

# define READ	0
# define WRITE	1
# define CMD_NOT_FOUND	127

typedef struct s_cmd	t_cmd;
struct s_cmd
{
	char	**cmds;
	char	*path;
	bool	is_rel;
	bool	is_abs;
	pid_t	pid;
	int		fd_dup_for;
};

typedef struct s_pipe	t_pipe;
struct s_pipe
{
	// argv, env
	char	**argv;
	char	**env;
	char	**env_paths;
	// cmd
	t_cmd	*cmd1;
	t_cmd	*cmd2;
	// file
	char	*infile_name;
	char	*outfile_name;
	// pipe
	int		pipe_fd[2];
	int		file_fd[2];
	int		exit_status;
};

/* inputs.c */
void	get_inputs(t_pipe *p, int exit_num_if_fail);

/* fd.c */
int		open_infile(t_pipe *p);
int		open_outfile(t_pipe *p);

/* pipe.c */
int		exec_pipe(t_pipe *p, int exit_num_if_fail);

/* ft_split_pipex.c */
char	**ft_split_pipex(const char *str, char delim, char set);

/* utils.c */
void	free_allocs(t_pipe *p);
void	free_and_ret_null(char **alloc_str);

/* errors.c */
void	errmsg_str1_str2(char *str1, char *str2);
void	errmsg_str1_str2_exit(char *str1, char *str2, int exit_no);
void	perror_and_exit(char *err_str, int exit_no);

/* for debug */
//void	fprint_2d_arr(char **array, char *info_str, FILE *fp);
//void	print_2d_arr(char **array, char *info_str);
//void	debug_msg_str1_n_str2_nl(char *str1, int n, char *str2);

#endif
