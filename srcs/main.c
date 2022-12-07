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

void	init_p(t_pipe *p, char ***argv, char ***envp)
{
	p->env = *envp;
	p->av = *argv;
	p->cmd_path1 = NULL;
	p->cmd_path2 = NULL;
	p->input_cmd1 = NULL;
	p->input_cmd2 = NULL;
	p->env_paths = NULL;
	p->infile = NULL;
	p->outfile = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	p;

	if (argc != 5)
		errmsg_and_exit(\
		"[Invalid arguments] Hint:$> ./pipex infile \"cmd1\" \"cmd2\" outfile\n"\
		"    it's same as operate:$> < infile cmd1 | cmd2 > outfile", \
		EXIT_FAILURE);
	init_p(&p, &argv, &envp);
	// get_input
	get_env_paths(&p, EXIT_FAILURE);
	get_cmds_from_argv(&p, EXIT_FAILURE);
	get_file_names(&p, EXIT_FAILURE);
	// set fd
	set_file_fds(&p, EXIT_FAILURE);
	dup_fds(&p, EXIT_FAILURE);
	// pipe
	make_pipe(&p, EXIT_FAILURE);
	child_for_cmd1(&p, EXIT_FAILURE);
	child_for_cmd2(&p, EXIT_FAILURE);
	close_and_frees(&p);
	wait_pids(&p, EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

#ifdef LESKS

__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q pipex");
}

#endif