/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 09:58:36 by takira            #+#    #+#             */
/*   Updated: 2022/12/09 09:58:38 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex.h"

void	perror_and_exit(char *err_str, int exit_no)
{
	perror(err_str);
	exit (exit_no);
}

void	errmsg_str1_str2_exit(char *str1, char *str2, int exit_no)
{
	ft_putstr_fd("[Error] ", STDERR_FILENO);
	ft_putstr_fd(str1, STDERR_FILENO);
	if (str2)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(str2, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	exit (exit_no);
}

void	errmsg_str1_str2(char *str1, char *str2)
{
	ft_putstr_fd("[Error] ", STDERR_FILENO);
	ft_putstr_fd(str1, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(str2, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
