/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:48:30 by takira            #+#    #+#             */
/*   Updated: 2022/12/09 21:48:09 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex_bonu.h"

/* functions */
int	file_open_for(char *filename, open_purpose purpose)
{
	if (purpose == FILE_READ)
		return (open(filename, O_RDONLY));
	if (purpose == FILE_OVERWRITE)
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666));
	if (purpose == FILE_APPEND)
		return (open(filename, O_CREAT | O_WRONLY | O_APPEND, 0666));
	return (-1);
}

int	open_infile_b(t_pipe *p)
{
	p->file_fd[READ] = file_open_for(p->infile_name, FILE_READ);
	if (p->file_fd[READ] < 0)
	{
		errmsg_str1_str2_b("no such file or directory", p->infile_name);
		return (FAIL);
	}
	return (PASS);
}

int	open_outfile_b(t_pipe *p)
{
	p->file_fd[WRITE] = file_open_for(p->outfile_name, FILE_OVERWRITE);
	if (p->file_fd[WRITE] < 0)
	{
		errmsg_str1_str2_b("permission denied", p->outfile_name);
		p->exit_status = EXIT_FAILURE;
		return (FAIL);
	}
	return (PASS);
}
