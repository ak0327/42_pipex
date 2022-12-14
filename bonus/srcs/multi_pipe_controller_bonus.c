/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:40:09 by takira            #+#    #+#             */
/*   Updated: 2022/12/12 18:40:11 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex_bonus.h"

/* prototype declaration */
static int	exec_pipe_parent(t_pipe *p, int exit_fail_no);

/* functions */
int	multi_pipe_controller(t_pipe *p, int exit_fail_no)
{
	if (open_outfile_b(p) == FAIL)
		return (exit_fail_no);
	if (dup2(p->i_file_fd[WRITE], STDOUT_FILENO) < 0)
		exit_with_perror_free_b("dup2", exit_fail_no, p);
	if (close(p->i_file_fd[WRITE]) < 0)
		exit_with_perror_free_b("close", exit_fail_no, p);
	p->i_exit_status = exec_pipe_parent(p, exit_fail_no);
	return (p->i_exit_status);
}

static int	exec_pipe_parent(t_pipe *p, int exit_fail_no)
{
	pid_t	pid;
	int		status;
	size_t	i;

	pid = fork();
	if (pid < 0)
		exit_with_perror_free_b("fork", exit_fail_no, p);
	if (pid == 0)
		exec_i_th_pipe(p, exit_fail_no, p->s_cmd_cnt - 1);
	i = 0;
	while (i++ < p->s_cmd_cnt + 1)
		wait(&status);
	return (WEXITSTATUS(status));
}
