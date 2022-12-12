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
# define HERE_DOC		"here_doc"

# define PATH_RELATIVE	"./"
# define PATH_ABSOLUTE	"/"

# define READ	0
# define WRITE	1
# define CMD_NOT_FOUND	127

typedef struct s_pipe	t_pipe;
struct s_pipe
{
	// argv, env
	char	**c_argv;
	char	**c_env;
	char	**c_env_paths;
	// cmd
	t_list	*t_cmd_list;
	size_t	s_cmd_cnt;
	size_t	s_first_cmd_idx_in_argv;
	// here_doc
	char	*c_limiter;
	// file
	char	*c_infile_name;
	char	*c_outfile_name;
	// pipe
	int		i_pipe_fd[2];
	int		i_file_fd[2];
	int		i_exit_status;
};

typedef struct s_cmd	t_cmd;//TODO:malloc
struct s_cmd
{
	char	**c_cmds;//TODO:malloc
	char	*c_path; //TODO:malloc when execute cmd
	bool	b_is_rel;
	bool	b_is_abs;
	pid_t	t_pid;
	int		i_fd_dup_for;
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
void	init_pipe_params_b(t_pipe *p, char ***argv, size_t cmd_cnt, char *eof);

/* inputs_bonus.c */
void	get_env_paths_b(t_pipe *p, int exit_num_if_fail);
void	get_input_cmds(t_pipe *p, int exit_num_if_fail);
void	get_file_names_b(t_pipe *p, int exit_num_if_fail);


void	get_inputs_b(t_pipe *p, int exit_num_if_fail);

/* open_file_bonus.c */
int		open_infile_b(t_pipe *p);
int		open_outfile_b(t_pipe *p);
int		file_open_for(char *filename, open_purpose purpose);

/* multi_pipe_bonus.c */
int		multi_pipe_controller(int argc, char **argv);

/* here_doc_bonus.c */
int		here_doc(char **argv);

/* pipe_bonus.c */
int		exec_pipe_b(t_pipe *p, int exit_num_if_fail);

/* ft_split_set_bonus.c */
char	**ft_split_set_b(const char *str, char delim, char set);

/* envver_expansion_bonus.c */
char	*expansion_env_variable(char *line);

/* env_lsts_bonus.c */
t_list	*get_env_lst(void);
char	*find_val_by_key(t_list *envs, char *search_key);

/* utils_bonus.c */
void	ft_lstiter_fd(t_list *lst, int fd, void (*func)(char *, int));

/* free_alloc_bonus.c */
void	free_allocs_b(t_pipe *p);
void	free_and_ret_null_b(char **alloc_str);
void	free_env_elem(void *content);

/* errors_bonus.c */
void	exit_with_msg_and_free_allocs(char *s1, char *s2, int exit_no, t_pipe *p);
void	errmsg_str1_str2_b(char *str1, char *str2);
//void	exit_with_msg_and_free_allocs(char *str1, char *str2, int exit_no);
void	perror_and_exit_b(char *err_str, int exit_no);

/* for debug */
void	fprint_2d_arr_b(char **array, char *info_str, FILE *fp);
void	print_2d_arr_b(char **array, char *info_str);
void	debug_msg_str1_n_str2_nl_b(char *str1, int n, char *str2);
void	print_path(void *content);

#endif
