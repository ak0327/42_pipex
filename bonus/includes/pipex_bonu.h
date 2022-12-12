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

typedef struct s_env_elem	t_env_elem;
struct s_env_elem
{
	char	*key;
	char	*val;
};

typedef enum
{
	FILE_READ,
	FILE_OVERWRITE,
	FILE_APPEND
}	open_purpose;

/* inputs_bonus.c */
void	get_inputs_b(t_pipe *p, int exit_num_if_fail);

/* open_file_bonus.c */
int		open_infile_b(t_pipe *p);
int		open_outfile_b(t_pipe *p);
int		file_open_for(char *filename, open_purpose purpose);


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
void	errmsg_str1_str2_b(char *str1, char *str2);
void	errmsg_str1_str2_exit_b(char *str1, char *str2, int exit_no);
void	perror_and_exit_b(char *err_str, int exit_no);

/* for debug */
void	fprint_2d_arr_b(char **array, char *info_str, FILE *fp);
void	print_2d_arr_b(char **array, char *info_str);
void	debug_msg_str1_n_str2_nl_b(char *str1, int n, char *str2);
void	print_path(void *content);

#endif
