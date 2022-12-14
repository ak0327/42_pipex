/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 13:28:49 by takira            #+#    #+#             */
/*   Updated: 2022/12/04 13:28:50 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/errno.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>

# include "./../../lib/libft/libft.h"
# include "./../../lib/libftprintf/ft_printf.h"
# include "./../../lib/libgnl/get_next_line.h"

# define SPACES			"\t\n\v\f\r "
# define TRIM_CHARS		"\t\n\v\f\r '"
# define HERE_DOC_FLG	"here_doc"

# define PATH_REL	"./"
# define PATH_ABS	"/"

# define READ		0
# define WRITE		1
# define BUF_SIZE	256

# define CMD_NOT_FOUND		127
# define CMD_IDX_MULTI_PIPE	2
# define CMD_IDX_HERE_DOC	3
# define LIMITER_IDX		2

typedef struct s_pipe	t_pipe;
struct s_pipe
{
	// argv, env
	char	**c_argv;
	char	**c_environ;
	char	**c_paths;//TODO:malloc
	// cmd
	t_list	*t_cmd_list;
	size_t	s_cmd_cnt;
	size_t	s_first_cmd_idx_in_argv;
	// here_doc
	char	*c_limiter;
	t_list	*t_here_doc_contents;
	bool	is_here_doc_success;
	// file
	char	*c_infile_name;
	char	*c_outfile_name;
	int		i_file_fd[2];
	// pipe
	int		i_exit_status;
};

typedef struct s_cmd	t_cmd;//TODO:malloc
struct s_cmd
{
	char	**c_cmds;// TODO:malloc
	char	*c_path;// TODO:malloc when execute cmd
	bool	is_rel;
	bool	is_abs;
	int		t_pid;
};

typedef struct s_env_elem	t_env_elem;
struct s_env_elem
{
	char	*c_key;
	char	*c_val;
};

typedef enum
{
	FILE_READ,
	FILE_OVERWRITE,
	FILE_APPEND
}	open_purpose;

/* init_pipe_params_bonus.c */
void	init_controller(t_pipe *p, int argc, char ***argv, int exit_fail_no);

/* inputs_bonus.c */
void	get_env_paths_b(t_pipe *p, int exit_num_if_fail);
void	get_input_cmds(t_pipe *p, int exit_num_if_fail);
void	get_file_names_b(t_pipe *p, int exit_num_if_fail);

/* open_file_bonus.c */
int		open_outfile_b(t_pipe *p);
int		file_open_for(char *filename, open_purpose purpose);
int		open_infile_b(t_pipe *p);

/* multi_pipe_bonus.c */
int		multi_pipe_controller(t_pipe *p, int exit_fail_no);

/* exec_pipe_bonus.c */
int		pipe_parent(t_pipe *p, int exit_fail_no);
void	exec_i_th_pipe(t_pipe *p, int exit_fail_no, size_t pipe_no);

/* exec_cmd_bonus.c */
void	exec_i_th_cmd(t_pipe *p, t_cmd *cmd, int exit_fail_no);

/* here_doc_bonus.c */
bool	get_here_doc(t_pipe *p);

/* ft_split_set_bonus.c */
char	**ft_split_set_b(const char *str, char delim, char set);

/* envver_expansion_bonus.c */
char	*expansion_env_variable(char *line, t_list *envs);

/* env_lsts_bonus.c */
t_list	*get_env_lst(t_pipe *p, int exit_fail_no);
char	*find_val_by_key(t_list *envs, char *search_key);

/* utils_bonus.c */
void	ft_lstiter_fd(t_list *lst, int fd, void (*func)(char *, int));

/* free_alloc_bonus.c */
void	free_allocs_b(t_pipe *p);
void	free_and_ret_null_b(char **alloc_str);
void	free_env_elem(void *content);

/* errors_bonus.c */
void	exit_with_msg_and_frees(char *s1, char *s2, int exit_no, t_pipe *p);
void	errmsg_str1_str2_b(char *str1, char *str2);
//void	exit_with_msg_and_frees(char *str1, char *str2, int exit_no);
void	perror_and_exit_b(char *err_str, int exit_no);
void	errmsg_invalid_arg(int exit_fail_no);

/* for debug */
void	fprint_2d_arr_b(char **array, char *info_str, FILE *fp);
void	print_2d_arr_b(char **array, char *info_str);
void	debug_msg_str1_n_str2_nl_b(char *str1, int n, char *str2);
void	debug_msg_str1_n_str2_b(char *str1, int n, char *str2);
void	print_path(void *content);

#endif
