/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:48:30 by takira            #+#    #+#             */
/*   Updated: 2022/12/06 20:48:31 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex.h"

/* prototype declaration */
static void	set_file_fds(t_pipe *p, int fail_exit_no);
static void	dup_fds(t_pipe *p, int fail_exit_no);

/* functions */
void	set_fd(t_pipe *p, int fail_exit_no)
{
	set_file_fds(p, fail_exit_no);
	dup_fds(p, fail_exit_no);
}

static void	set_file_fds(t_pipe *p, int fail_exit_no)
{
	p->file_fd[READ] = open(p->infile, O_RDONLY);
	p->file_fd[WRITE] = open(p->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (p->file_fd[READ] < 0 || p->file_fd[WRITE] < 0)
		errmsg_and_exit("[Error] Fail to open file", fail_exit_no);
}

static void	dup_fds(t_pipe *p, int fail_exit_no)
{
	if (dup2(p->file_fd[READ], STDIN_FILENO) < 0)
		perror_and_exit("dup2", fail_exit_no);
	close(p->file_fd[READ]);
	if (dup2(p->file_fd[WRITE], STDOUT_FILENO) < 0)
		perror_and_exit("dup2", fail_exit_no);
	close(p->file_fd[WRITE]);
}
