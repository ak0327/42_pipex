/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:48:30 by takira            #+#    #+#             */
/*   Updated: 2022/12/06 20:48:31 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex.h"

/* functions */
void	open_infile(t_pipe *p, int exit_no_if_fail)
{
	p->file_fd[READ] = open(p->infile_name, O_RDONLY);
	if (p->file_fd[READ] < 0)
		errmsg_str1_str2_exit(\
		"no such file or directory", p->infile_name, exit_no_if_fail);
	if (dup2(p->file_fd[READ], STDIN_FILENO) < 0)
		perror_and_exit("dup2", exit_no_if_fail);
	close(p->file_fd[READ]);
}

void	open_outfile(t_pipe *p, int exit_no_if_fail)
{
	p->file_fd[WRITE] \
	= open(p->outfile_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (p->file_fd[WRITE] < 0)
		errmsg_str1_str2_exit(\
		"permission denied:", p->outfile_name, exit_no_if_fail);
	if (dup2(p->file_fd[WRITE], STDOUT_FILENO) < 0)
		perror_and_exit("dup2", exit_no_if_fail);
	close(p->file_fd[WRITE]);
}
