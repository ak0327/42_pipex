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
# define HERE_DOC_FLG	"here_doc"

# define PATH_REL	"./"
# define PATH_ABS	"/"
# define PATH_FLG	"PATH="
# define VAR_DELIM	"\n \"$"

# define READ		0
# define WRITE		1
# define BUF_SIZE	256

# define CMD_NOT_FOUND		127
# define CMD_IDX_MULTI_PIPE	2
# define CMD_IDX_HERE_DOC	3
# define LIMITER_IDX		2
# define CMD_CNT_HERE_DOC	2

typedef struct s_pipe
{
	char	**c_argv;
	char	**c_environ;
	char	**c_paths_m;
	t_list	*t_cmd_list_m;
	size_t	s_cmd_cnt;
	size_t	s_first_cmd_idx_in_argv;
	char	*c_limiter_m;
	t_list	*t_here_doc_contents;
	char	*c_infile_name_m;
	char	*c_outfile_name_m;
	int		i_file_fd[2];
	int		i_exit_status;
}			t_pipe;

typedef struct s_cmd
{
	char	**c_cmds_m;
	char	*c_path_m;
	bool	is_rel;
	bool	is_abs;
	bool	is_path;
	int		t_pid;
}			t_cmd;

typedef struct s_env_elem
{
	char	*c_key_m;
	char	*c_val_m;
}			t_env_elem;

typedef enum s_open_purpose
{
	F_READ,
	F_OVERWRITE,
	F_APPEND
}	t_open_purpose;

/* init_pipe_params_bonus.c */
void	init_controller(t_pipe *p, int argc, char ***argv, int exit_fail_no);

/* inputs_bonus.c */
void	get_env_paths_b(t_pipe *p, int exit_fail_no);
void	get_input_cmds(t_pipe *p, int exit_fail_no);
void	get_file_names_b(t_pipe *p, int exit_fail_no);

/* open_file_bonus.c */
int		open_outfile_b(t_pipe *p);
int		file_open_for(char *filename, t_open_purpose purpose);
int		open_infile_b(t_pipe *p);

/* multi_pipe_controller_bonus.c */
int		multi_pipe_controller(t_pipe *p, int exit_fail_no);

/* exec_pipe_bonus.c */
void	exec_i_th_pipe(t_pipe *p, int exit_fail_no, size_t pipe_no);

/* exec_cmd_bonus.c */
void	exec_i_th_cmd(t_pipe *p, t_cmd *cmd, int exit_fail_no);

/* here_doc_bonus.c */
int		get_heredoc_contents_to_lst(t_pipe *p);

/* envver_expansion_bonus.c */
char	*expand_env_var_controller(char *line, t_list *envs);

/* env_lsts_bonus.c */
t_list	*get_env_lst(t_pipe *p, int exit_fail_no);
char	*search_val_in_envs(t_list *envs, char *search_key);

/* utils_bonus.c */
void	ft_lstiter_fd(t_list *lst, int fd, void (*func)(char *, int));

/* free_alloc_bonus.c */
void	free_allocs_b(t_pipe *p);
void	free_1d_array_b(char **alloc_str);
void	free_env_elems(void *content);

/* errors_bonus.c */
void	exit_with_errmsg_invalid_arg(int exit_fail_no);
void	exit_with_errmsg_and_free_b(char *s1, char *s2, int exit_no, t_pipe *p);
void	exit_with_perror_free_b(char *err_str, int exit_no, t_pipe *p);
void	put_errmsg_str1_str2_b(char *str1, char *str2);

/* for debug */
//void	fprint_2d_arr_b(char **array, char *info_str, FILE *fp);
//void	print_2d_arr_b(char **array, char *info_str);
//void	debug_msg_str1_n_str2_nl_b(char *str1, int n, char *str2);
//void	debug_msg_str1_n_str2_b(char *str1, int n, char *str2);
//void	print_path(void *content);

#endif
