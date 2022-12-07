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
static void	get_env_paths(t_pipe *p, int fail_exit_no);
static void	get_cmds_from_argv(t_pipe *p, int fail_exit_no);
static void	get_file_names(t_pipe *p, int fail_exit_no);

/* functions */
void	get_inputs(t_pipe *p, int fail_exit_no)
{
	get_env_paths(p, fail_exit_no);
	get_cmds_from_argv(p, fail_exit_no);
	get_file_names(p, fail_exit_no);
}

static void	get_env_paths(t_pipe *p, int fail_exit_no)
{
	size_t	i;

	i = 0;
	if (!p->env)
		errmsg_and_exit("[Error] Envp not exit", fail_exit_no);
	while (p->env[i] && ft_strncmp(p->env[i], "PATH=", 5) != 0)
		i++;
	if (!p->env[i])
		errmsg_and_exit("[Error] PATH in envp not exit", fail_exit_no);
	p->env_paths = ft_split(&p->env[i][5], ':');
	if (!p->env_paths)
		errmsg_and_exit("[Error] Fail to get PATH in envp", fail_exit_no);
}

static void	get_cmds_from_argv(t_pipe *p, int fail_exit_no)
{
	p->input_cmd1 = ft_split(p->av[2], ' ');
	p->input_cmd2 = ft_split(p->av[3], ' ');
	if (!p->input_cmd1 || !p->input_cmd2)
		errmsg_and_exit("[Error] Fail to get cmd1 or cmd2", fail_exit_no);
}

static void	get_file_names(t_pipe *p, int fail_exit_no)
{
	p->infile = ft_strtrim(p->av[1], SPACES);
	p->outfile = ft_strtrim(p->av[4], SPACES);
	if (!ft_strlen_ns(p->infile) || !ft_strlen_ns(p->outfile))
		errmsg_and_exit("[Error] Fail to get file name", fail_exit_no);
}
