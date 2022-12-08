/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:42:08 by takira            #+#    #+#             */
/*   Updated: 2022/12/04 12:42:10 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex.h"

static void	init_pipe_params(t_pipe *p, char ***argv)
{
	extern char	**environ;

	p->av = *argv;
	p->env = environ;
	p->env_paths = NULL;
	p->input_cmd1 = NULL;
	p->input_cmd2 = NULL;
	p->path_cmd1 = NULL;
	p->path_cmd2 = NULL;
	p->is_cmd1_relative = false;
	p->is_cmd2_relative = false;
	p->infile_name = NULL;
	p->outfile_name = NULL;
	p->num_of_cmds = 2;
	p->exit_status = EXIT_SUCCESS;
}

int	main(int argc, char **argv)
{
	t_pipe	p;

	if (argc != 5)
		errmsg_and_exit(\
		"[Invalid arguments] Hint:$> ./pipex infile \"cmd1\" \"cmd2\" outfile\n"\
		"    it's same as operate:$> < infile_name cmd1 | cmd2 > outfile_name", \
		EXIT_FAILURE);
	init_pipe_params(&p, &argv);
	get_inputs(&p, EXIT_FAILURE);
	set_file_fds(&p, EXIT_FAILURE);
	exec_pipe(&p, EXIT_FAILURE);
	debug_msg_str1_n_str2_nl("main exit_status:", p.exit_status, "");
	return (p.exit_status);
}

#ifdef LESKS

__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q pipex");
}

#endif
