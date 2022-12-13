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

int open_infile_or_here_doc(t_pipe *p)
{
	if (p->c_limiter)
		return (connect_here_doc_to_stdin(p));
	p->i_file_fd[READ] = file_open_for(p->c_infile_name, FILE_READ);
	if (p->i_file_fd[READ] < 0)
	{
		errmsg_str1_str2_b("no such file or directory", p->c_infile_name);
		return (FAIL);
	}
	return (PASS);
}

int	open_outfile_b(t_pipe *p)
{
	if (p->c_limiter)
		p->i_file_fd[WRITE] = file_open_for(p->c_outfile_name, FILE_APPEND);
	else
		p->i_file_fd[WRITE] = file_open_for(p->c_outfile_name, FILE_OVERWRITE);
	if (p->i_file_fd[WRITE] < 0)
	{
		errmsg_str1_str2_b("permission denied", p->c_outfile_name);
		p->i_exit_status = EXIT_FAILURE;
		return (FAIL);
	}
	return (PASS);
}
