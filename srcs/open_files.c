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
int	open_infile(t_pipe *p)
{
	p->file_fd[READ] = open(p->infile_name, O_RDONLY);
	if (p->file_fd[READ] < 0)
	{
		errmsg_str1_str2("no such file or directory", p->infile_name);
		return (FAIL);
	}
	return (PASS);
}

int	open_outfile(t_pipe *p)
{
	const int	oflag = O_CREAT | O_WRONLY | O_TRUNC;

	p->file_fd[WRITE] = open(p->outfile_name, oflag, 0666);
	if (p->file_fd[WRITE] < 0)
	{
		errmsg_str1_str2("permission denied", p->outfile_name);
		p->exit_status = EXIT_FAILURE;
		return (FAIL);
	}
	return (PASS);
}
