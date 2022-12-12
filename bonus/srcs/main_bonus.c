/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:42:08 by takira            #+#    #+#             */
/*   Updated: 2022/12/09 21:48:01 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex_bonu.h"

static void	init_pipe_params_b(t_pipe *p, char ***argv)
{
	extern char	**environ;

	p->argv = *argv;
	p->env = environ;
	p->env_paths = NULL;
	p->infile_name = NULL;
	p->outfile_name = NULL;
	p->exit_status = EXIT_SUCCESS;
}

static void	init_cmd_params_b(t_pipe *p)
{
	p->cmd1 = (t_cmd *)malloc(sizeof(t_cmd));
	p->cmd2 = (t_cmd *)malloc(sizeof(t_cmd));
	if (!p->cmd1 || !p->cmd2)
	{
		free_allocs_b(p);
		errmsg_str1_str2_exit_b("Fail to malloc", "", EXIT_FAILURE);
	}
	p->cmd1->cmds = NULL;
	p->cmd2->cmds = NULL;
	p->cmd1->path = NULL;
	p->cmd2->path = NULL;
	p->cmd1->is_rel = false;
	p->cmd2->is_rel = false;
	p->cmd1->is_abs = false;
	p->cmd2->is_abs = false;
	p->cmd1->fd_dup_for = STDOUT_FILENO;
	p->cmd2->fd_dup_for = STDIN_FILENO;
	p->cmd1->pid = -1;
	p->cmd2->pid = -1;
}

int	main(int argc, char **argv)
{
	t_pipe	p;
	int		exit_status;

	// argc == ??
	// -> argv[2] == "Heredoc"
	// -> else pipe

	if (argc != 5)
		errmsg_str1_str2_exit_b(\
		"Invalid arguments. Input following cmds (1), it's operate same as (2)\n"\
		" 1) $ ./pipex infile_name \"cmd1\" \"cmd2\" outfile_name\n"\
		" 2) $ < infile_name cmd1 | cmd2 > outfile_name", \
		NULL, EXIT_FAILURE);
	init_pipe_params_b(&p, &argv);
	init_cmd_params_b(&p);
	get_inputs_b(&p, EXIT_FAILURE);
	exit_status = exec_pipe_b(&p, EXIT_FAILURE);
	free_allocs_b(&p);
	return (exit_status);
}

#ifdef LESKS

__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q pipex");
}

#endif
