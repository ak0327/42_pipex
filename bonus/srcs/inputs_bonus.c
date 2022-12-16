/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:21:22 by takira            #+#    #+#             */
/*   Updated: 2022/12/06 20:21:23 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex_bonus.h"

/* prototype declaration */
static t_cmd	*get_i_th_cmd_from_argv(t_pipe *p, size_t idx);
static bool		get_is_path(const char *cmd_head);

/* functions */
void	get_env_paths_b(t_pipe *p, int exit_fail_no)
{
	size_t			i;
	size_t			j;
	const size_t	len = ft_strlen_ns(PATH_FLG);

	if (!p->c_environ)
		exit_with_errmsg_and_free_b(\
		"Environment args not exist", NULL, exit_fail_no, p);
	i = 0;
	j = 0;
	while (p->c_environ[i] && ft_strncmp(p->c_environ[i], PATH_FLG, len) != 0)
		i++;
	if (!p->c_environ[i])
		p->c_environ[i] = "";
	else
		j = 5;
	p->c_paths_m = ft_split(&p->c_environ[i][j], ':');
	if (!p->c_paths_m)
		exit_with_errmsg_and_free_b(\
		"Fail to get env path", NULL, exit_fail_no, p);
}

void	get_input_cmds(t_pipe *p, int exit_fail_no)
{
	size_t	i;
	t_list	*new_node_m;
	t_cmd	*new_cmd_m;

	i = 0;
	while (i < p->s_cmd_cnt)
	{
		new_cmd_m = get_i_th_cmd_from_argv(p, i + p->s_first_cmd_idx_in_argv);
		new_node_m = ft_lstnew(new_cmd_m);
		if (!new_cmd_m || !new_node_m)
			exit_with_perror_free_b("malloc", exit_fail_no, p);
		ft_lstadd_back(&p->t_cmd_list_m, new_node_m);
		i++;
	}
}

static t_cmd	*get_i_th_cmd_from_argv(t_pipe *p, size_t idx)
{
	t_cmd	*new_cmd_m;

	new_cmd_m = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd_m)
		return (NULL);
	new_cmd_m->c_cmds_m = NULL;
	new_cmd_m->c_path_m = NULL;
	new_cmd_m->is_rel = false;
	new_cmd_m->is_abs = false;
	new_cmd_m->t_pid = -1;
	new_cmd_m->c_cmds_m = ft_split_set(p->c_argv[idx], ' ', '\'');
	if (!new_cmd_m->c_cmds_m)
		return (NULL);
	new_cmd_m->is_path = get_is_path(new_cmd_m->c_cmds_m[0]);
	return (new_cmd_m);
}

static bool	get_is_path(const char *cmd_head)
{
	if (!cmd_head)
		return (false);
	if (cmd_head[0] == '/')
		return (true);
	if (cmd_head[0] == '.' && cmd_head[1] == '/')
		return (true);
	return (false);
}

void	get_file_names_b(t_pipe *p, int exit_fail_no)
{
	const size_t	outfile_idx = p->s_first_cmd_idx_in_argv + p->s_cmd_cnt;

	if (!p->c_limiter_m)
		p->c_infile_name_m = ft_strtrim(p->c_argv[1], SPACES);
	p->c_outfile_name_m = ft_strtrim(p->c_argv[outfile_idx], SPACES);
	if ((!p->c_limiter_m && !ft_strlen_ns(p->c_infile_name_m)) \
	|| !ft_strlen_ns(p->c_outfile_name_m))
		exit_with_errmsg_and_free_b(\
		"Fail to get file name", NULL, exit_fail_no, p);
}
