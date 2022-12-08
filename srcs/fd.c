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
static void	open_files(t_pipe *p, int exit_no_if_fail);
static void	dup_fds(t_pipe *p, int exit_no_if_fail);

/* functions */
void	set_file_fds(t_pipe *p, int exit_no_if_fail)
{
	open_files(p, exit_no_if_fail);
	dup_fds(p, exit_no_if_fail);
}

static void	open_files(t_pipe *p, int exit_no_if_fail)
{
	p->file_fd[READ] \
	= open(p->infile_name, O_RDONLY);
	p->file_fd[WRITE] \
	= open(p->outfile_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (p->file_fd[READ] < 0 || p->file_fd[WRITE] < 0)
		errmsg_and_exit("[Error] Fail to open file", exit_no_if_fail);
}

static void	dup_fds(t_pipe *p, int exit_no_if_fail)
{
	if (dup2(p->file_fd[READ], STDIN_FILENO) < 0)
		perror_and_exit("dup2", exit_no_if_fail);
	close(p->file_fd[READ]);
	if (dup2(p->file_fd[WRITE], STDOUT_FILENO) < 0)
		perror_and_exit("dup2", exit_no_if_fail);
	close(p->file_fd[WRITE]);
}
