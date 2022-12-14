/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 09:58:36 by takira            #+#    #+#             */
/*   Updated: 2022/12/09 21:47:43 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex_bonus.h"

void	exit_with_errmsg_invalid_arg(int exit_fail_no)
{
	ft_putstr_fd(\
	"[Error] Invalid args. Input following cmds 1-1) or 2-1),\n"\
	"        It's operate same as 1-2) or 2-2).\n"\
	" ----------------------------------------------------------------\n"\
	" * 1-1)$> ./pipex infile_name \"cmd1\" \"cmd2\"..\"cmdn\" outfile_name\n"\
	"   1-2)$> < infile_name cmd1 | cmd2 |..| cmdn > outfile_name\n"\
	" ----------------------------------------------------------------\n"\
	" * 2-1)$> ./pipex here_doc LIMITER \"cmd1\" \"cmd2\" outfile_name\n"\
	"   2-2)$> cmd1 << LIMITER | cmd2 >> outfile_name\n"\
	" ----------------------------------------------------------------\n", \
	STDERR_FILENO);
	exit (exit_fail_no);
}

void	exit_with_perror_free_b(char *err_str, int exit_no, t_pipe *p)
{
	perror(err_str);
	free_allocs_b(p);
	exit (exit_no);
}

void	exit_with_errmsg_and_free_b(char *s1, char *s2, int exit_no, t_pipe *p)
{
	ft_putstr_fd("[Error] ", STDERR_FILENO);
	ft_putstr_fd(s1, STDERR_FILENO);
	if (s2)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(s2, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	free_allocs_b(p);
	exit (exit_no);
}

void	put_errmsg_str1_str2_b(char *str1, char *str2)
{
	ft_putstr_fd("[Error] ", STDERR_FILENO);
	ft_putstr_fd(str1, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(str2, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
