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
static void	get_env_paths_b(t_pipe *p, int exit_num_if_fail);
static void	get_cmds_from_argv_b(t_pipe *p, int exit_num_if_fail);
static void	check_cmds_path_b(t_pipe *p);
static void	get_file_names_b(t_pipe *p, int exit_num_if_fail);

/* functions */
void	get_inputs_b(t_pipe *p, int exit_num_if_fail)
{
	get_env_paths_b(p, exit_num_if_fail);
	get_cmds_from_argv_b(p, exit_num_if_fail);
	check_cmds_path_b(p);
	get_file_names_b(p, exit_num_if_fail);
}

static void	get_env_paths_b(t_pipe *p, int exit_num_if_fail)
{
	size_t	i;

	if (!p->env)
		errmsg_str1_str2_exit_b(\
		"Environment args not exist", NULL, exit_num_if_fail);
	i = 0;
	while (p->env[i] && ft_strncmp(p->env[i], "PATH=", 5) != 0)
		i++;
	if (!p->env[i])
	{
		p->env[i] = ft_strdup("");
		if (!p->env[i])
			errmsg_str1_str2_exit_b(\
			"Fail to get env path", NULL, exit_num_if_fail);
	}
	else
		p->env[i] += 5;
	p->env_paths = ft_split(p->env[i], ':');
	if (!p->env_paths)
		errmsg_str1_str2_exit_b(\
		"Fail to get env path", NULL, exit_num_if_fail);
}

static void	get_cmds_from_argv_b(t_pipe *p, int exit_num_if_fail)
{
	p->cmd1->cmds = ft_split_set_b(p->argv[2], ' ', '\'');
	p->cmd2->cmds = ft_split_set_b(p->argv[3], ' ', '\'');
	if (!p->cmd1->cmds || !p->cmd2->cmds)
		errmsg_str1_str2_exit_b(\
		"Fail to get cmd1 or cmd2", NULL, exit_num_if_fail);
}

static void	check_cmds_path_b(t_pipe *p)
{
	const size_t	path_relative_len = ft_strlen_ns(PATH_RELATIVE);
	const size_t	path_absolute_len = ft_strlen_ns(PATH_ABSOLUTE);

	if (p->cmd1->cmds[0])
	{
		if (ft_strncmp(p->cmd1->cmds[0], PATH_RELATIVE, path_relative_len) == 0)
			p->cmd1->is_rel = true;
		if (ft_strncmp(p->cmd1->cmds[0], PATH_ABSOLUTE, path_absolute_len) == 0)
			p->cmd1->is_abs = true;
	}
	if (p->cmd2->cmds[0])
	{
		if (ft_strncmp(p->cmd2->cmds[0], PATH_RELATIVE, path_relative_len) == 0)
			p->cmd2->is_rel = true;
		if (ft_strncmp(p->cmd2->cmds[0], PATH_ABSOLUTE, path_absolute_len) == 0)
			p->cmd2->is_abs = true;
	}
	print_2d_arr_b(p->cmd1->cmds, "cmd1");
	print_2d_arr_b(p->cmd2->cmds, "cmd2");
}

static void	get_file_names_b(t_pipe *p, int exit_num_if_fail)
{
	p->infile_name = ft_strtrim(p->argv[1], SPACES);
	p->outfile_name = ft_strtrim(p->argv[4], SPACES);
	if (!ft_strlen_ns(p->infile_name) || !ft_strlen_ns(p->outfile_name))
		errmsg_str1_str2_exit_b(\
		"Fail to get file name", NULL, exit_num_if_fail);
}