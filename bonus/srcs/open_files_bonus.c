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

#include "./../includes/pipex_bonus.h"

/* functions */
int	file_open_for(char *filename, t_open_purpose purpose)
{
	if (purpose == F_READ)
		return (open(filename, O_RDONLY));
	if (purpose == F_OVERWRITE)
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666));
	if (purpose == F_APPEND)
		return (open(filename, O_CREAT | O_WRONLY | O_APPEND, 0666));
	return (-1);
}

int	open_infile_b(t_pipe *p)
{
	if (p->c_limiter_m)
		return (PASS);
	p->i_file_fd[READ] = file_open_for(p->c_infile_name_m, F_READ);
	if (p->i_file_fd[READ] < 0)
	{
		put_errmsg_str1_str2_b("no such file or directory", p->c_infile_name_m);
		return (FAIL);
	}
	return (PASS);
}

int	open_outfile_b(t_pipe *p)
{
	if (p->c_limiter_m)
		p->i_file_fd[WRITE] = file_open_for(p->c_outfile_name_m, F_APPEND);
	else
		p->i_file_fd[WRITE] = file_open_for(p->c_outfile_name_m, F_OVERWRITE);
	if (p->i_file_fd[WRITE] < 0)
	{
		put_errmsg_str1_str2_b("permission denied", p->c_outfile_name_m);
		p->i_exit_status = EXIT_FAILURE;
		return (FAIL);
	}
	return (PASS);
}
