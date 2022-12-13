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

#include "./../includes/pipex_bonu.h"

/* prototype declaration */
static t_cmd	*get_i_th_cmd_from_argv(t_pipe *p, size_t idx);
static void		check_cmd_path_kind(t_cmd *cmd_node);

/* functions */

void	get_env_paths_b(t_pipe *p, int exit_num_if_fail)
{
	size_t	i;
	size_t	j;

	if (!p->c_environ)
		exit_with_msg_and_frees(\
        "Environment args not exist", NULL, exit_num_if_fail, p);
	i = 0;
	j = 0;
	while (p->c_environ[i] && ft_strncmp_ns(p->c_environ[i], "PATH=", 5) != 0)
		i++;
	if (!p->c_environ[i])
		p->c_environ[i] = "";
//		return ;
	else
		j = 5;
	p->c_paths = ft_split(&p->c_environ[i][j], ':');
	if (!p->c_paths)
		exit_with_msg_and_frees(\
        "Fail to get env path", NULL, exit_num_if_fail, p);
}

void	get_input_cmds(t_pipe *p, int exit_num_if_fail)
{
	size_t	i;
	t_list	*new_node;
	t_cmd	*new_cmd;

	i = 0;
	while (i < p->s_cmd_cnt)
	{
		new_cmd = get_i_th_cmd_from_argv(p, i + p->s_first_cmd_idx_in_argv);
		new_node = ft_lstnew(new_cmd);
		if (!new_cmd || !new_node)//TODO:free list in exitfunc?
			exit_with_msg_and_frees(\
        "Fail to get cmd", NULL, exit_num_if_fail, p);
		ft_lstadd_back(&p->t_cmd_list, new_node);
		i++;
	}
}

static void	check_cmd_path_kind(t_cmd *cmd_node)
{
	const size_t	path_relative_len = ft_strlen_ns(PATH_RELATIVE);
	const size_t	path_absolute_len = ft_strlen_ns(PATH_ABSOLUTE);

	if (cmd_node->c_cmds[0])
	{
		if (ft_strncmp_ns(cmd_node->c_cmds[0], PATH_RELATIVE, path_relative_len) == 0)
			cmd_node->is_rel = true;
		if (ft_strncmp_ns(cmd_node->c_cmds[0], PATH_ABSOLUTE, path_absolute_len) == 0)
			cmd_node->is_abs = true;
	}
}

static t_cmd	*get_i_th_cmd_from_argv(t_pipe *p, size_t idx)
{
	t_cmd	*new_cmd;

	// init
	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->c_cmds = NULL;
	new_cmd->c_path = NULL;
	new_cmd->is_rel = false;
	new_cmd->is_abs = false;
	new_cmd->t_pid = -1;
	new_cmd->c_cmds = ft_split_set_b(p->c_argv[idx], ' ', '\'');
	if (!new_cmd->c_cmds)
		return (NULL);
	check_cmd_path_kind(new_cmd);
	return (new_cmd);
}

void	get_file_names_b(t_pipe *p, int exit_num_if_fail) //TODO:free@Mandatory
{
	const size_t	outfile_idx = p->s_first_cmd_idx_in_argv + p->s_cmd_cnt;

	if (!p->c_limiter)
		p->c_infile_name = ft_strtrim(p->c_argv[1], SPACES);
	p->c_outfile_name = ft_strtrim(p->c_argv[outfile_idx], SPACES);
	if ((!p->c_limiter && !ft_strlen_ns(p->c_infile_name))\
	|| !ft_strlen_ns(p->c_outfile_name))
		exit_with_msg_and_frees(\
    "Fail to get file name", NULL, exit_num_if_fail, p);
}
