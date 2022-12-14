/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:21:22 by takira            #+#    #+#             */
/*   Updated: 2022/12/06 20:21:23 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex.h"

/* prototype declaration */
static void	get_env_paths(t_pipe *p, int exit_fail_no);
static void	get_cmds_from_argv(t_pipe *p, int exit_fail_no);
static void	check_cmds_path(t_pipe *p);
static void	get_file_names(t_pipe *p, int exit_fail_no);

/* functions */
void	get_inputs(t_pipe *p, int exit_fail_no)
{
	get_env_paths(p, exit_fail_no);
	get_cmds_from_argv(p, exit_fail_no);
	check_cmds_path(p);
	get_file_names(p, exit_fail_no);
}

static void	get_env_paths(t_pipe *p, int exit_fail_no)
{
	size_t			i;
	size_t			j;
	const size_t	len = ft_strlen_ns(PATH_FLG);

	if (!p->env)
		exit_with_errmsg_free(\
		"Environment args not exist", NULL, exit_fail_no, p);
	i = 0;
	j = 0;
	while (p->env[i] && ft_strncmp(p->env[i], PATH_FLG, len) != 0)
		i++;
	if (!p->env[i])
		p->env[i] = "";
	else
		j = 5;
	p->env_paths = ft_split(&p->env[i][j], ':');
	if (!p->env_paths)
		exit_with_errmsg_free(\
		"Fail to get env path", NULL, exit_fail_no, p);
}

static void	get_cmds_from_argv(t_pipe *p, int exit_fail_no)
{
	p->cmd1->cmds = ft_split_set(p->argv[2], ' ', '\'');
	p->cmd2->cmds = ft_split_set(p->argv[3], ' ', '\'');
	if (!p->cmd1->cmds || !p->cmd2->cmds)
		exit_with_errmsg_free(\
		"Fail to get cmd1 or cmd2", NULL, exit_fail_no, p);
}

static void	check_cmds_path(t_pipe *p)
{
	const size_t	path_rel_len = ft_strlen_ns(PATH_REL);
	const size_t	path_abs_len = ft_strlen_ns(PATH_ABS);

	if (p->cmd1->cmds[0])
	{
		if (ft_strncmp_ns(p->cmd1->cmds[0], PATH_REL, path_rel_len) == 0)
			p->cmd1->is_rel = true;
		if (ft_strncmp_ns(p->cmd1->cmds[0], PATH_ABS, path_abs_len) == 0)
			p->cmd1->is_abs = true;
	}
	if (p->cmd2->cmds[0])
	{
		if (ft_strncmp_ns(p->cmd2->cmds[0], PATH_REL, path_rel_len) == 0)
			p->cmd2->is_rel = true;
		if (ft_strncmp_ns(p->cmd2->cmds[0], PATH_ABS, path_abs_len) == 0)
			p->cmd2->is_abs = true;
	}
}

static void	get_file_names(t_pipe *p, int exit_fail_no)
{
	p->infile_name = ft_strtrim(p->argv[1], SPACES);
	p->outfile_name = ft_strtrim(p->argv[4], SPACES);
	if (!ft_strlen_ns(p->infile_name) || !ft_strlen_ns(p->outfile_name))
		exit_with_errmsg_free(\
		"Fail to get file name", NULL, exit_fail_no, p);
}
