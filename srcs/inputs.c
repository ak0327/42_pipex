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
static void	get_env_paths(t_pipe *p, int exit_no_if_fail);
static void	get_cmds_from_argv(t_pipe *p, int exit_no_if_fail);
static void	check_cmds_is_relative(t_pipe *p);
static void	get_file_names(t_pipe *p, int exit_no_if_fail);

/* functions */
void	get_inputs(t_pipe *p, int exit_no_if_fail)
{
	get_env_paths(p, exit_no_if_fail);
	get_cmds_from_argv(p, exit_no_if_fail);
	check_cmds_is_relative(p);
	get_file_names(p, exit_no_if_fail);
}

static void	get_env_paths(t_pipe *p, int exit_no_if_fail)
{
	size_t	i;

	if (!p->env)
		errmsg_str1_str2_exit(\
		"Environment args not exist", NULL, exit_no_if_fail);
	i = 0;
	while (p->env[i] && ft_strncmp(p->env[i], "PATH=", 5) != 0)
		i++;
	if (!p->env[i])
	{
		p->env[i] = ft_strdup("");//TODO free ?
		if (!p->env[i])
			errmsg_str1_str2_exit(\
			"Fail to get env path", NULL, exit_no_if_fail);
	}
	else
		p->env[i] += 5;
	p->env_paths = ft_split(p->env[i], ':');
	if (!p->env_paths)
		errmsg_str1_str2_exit(\
		"Fail to get env path", NULL, exit_no_if_fail);
}

static void	get_cmds_from_argv(t_pipe *p, int exit_no_if_fail)
{
	p->input_cmd1 = ft_split(p->av[2], ' ');
	p->input_cmd2 = ft_split(p->av[3], ' ');
	if (!p->input_cmd1 || !p->input_cmd2)
		errmsg_str1_str2_exit(\
		"Fail to get cmd1 or cmd2", NULL, exit_no_if_fail);
}

static void	check_cmds_is_relative(t_pipe *p)
{
	const size_t	path_current_len = ft_strlen_ns(PATH_CURRENT);

	if (p->input_cmd1[0])
		if (ft_strncmp(p->input_cmd1[0], PATH_CURRENT, path_current_len) == 0)
			p->is_cmd1_relative = true;
	if (p->input_cmd2[0])
		if (ft_strncmp(p->input_cmd2[0], PATH_CURRENT, path_current_len) == 0)
			p->is_cmd2_relative = true;
}

static void	get_file_names(t_pipe *p, int exit_no_if_fail)
{
	p->infile_name = ft_strtrim(p->av[1], SPACES);
	p->outfile_name = ft_strtrim(p->av[4], SPACES);
	if (!ft_strlen_ns(p->infile_name) || !ft_strlen_ns(p->outfile_name))
		errmsg_str1_str2_exit("Fail to get file name", NULL, exit_no_if_fail);
}
