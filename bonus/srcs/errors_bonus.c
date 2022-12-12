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

#include "./../includes/pipex_bonu.h"

void	perror_and_exit_b(char *err_str, int exit_no)
{
	perror(err_str);
	exit (exit_no);
}

void	exit_with_msg_and_free_allocs(char *s1, char *s2, int exit_no, t_pipe *p)
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

void	errmsg_str1_str2_b(char *str1, char *str2)
{
	ft_putstr_fd("[Error] ", STDERR_FILENO);
	ft_putstr_fd(str1, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(str2, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
