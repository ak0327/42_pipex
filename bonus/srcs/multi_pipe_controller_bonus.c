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

#include "./../includes/pipex_bonu.h"

/* prototype declaration */
//static int	wait_children(t_pipe *p, int exit_fail_no);

/* functions */
int	multi_pipe_controller(t_pipe *p, int exit_fail_no)
{
	if (open_outfile_b(p) == FAIL)
		return (exit_fail_no);
	if (dup2(p->i_file_fd[WRITE], STDOUT_FILENO) < 0)
		perror_and_exit_b("dup2", exit_fail_no);
	if (close(p->i_file_fd[WRITE]) < 0)
		perror_and_exit_b("close", exit_fail_no);
	p->i_exit_status = pipe_parent(p, exit_fail_no);
	return (p->i_exit_status);
}
