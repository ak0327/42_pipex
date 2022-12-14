/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:42:08 by takira            #+#    #+#             */
/*   Updated: 2022/12/09 21:48:01 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex_bonus.h"

int	main(int argc, char **argv)
{
	int		exit_status;
	t_pipe	p;

	exit_status = EXIT_SUCCESS;
	if (argc < 5)
		exit_with_errmsg_invalid_arg(EXIT_FAILURE);
	init_controller(&p, argc, &argv, EXIT_FAILURE);
	exit_status = multi_pipe_controller(&p, EXIT_FAILURE);
	free_allocs_b(&p);
	return (exit_status);
}

#ifdef LESKS

__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q pipex");
}

#endif
