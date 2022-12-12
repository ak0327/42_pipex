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

#include "./../includes/pipex_bonu.h"

int	main(int argc, char **argv)
{
	char	*here_doc_flg;
	int		exit_status;

	if (argc < 5)
		exit_with_msg_and_free_allocs(\
		"Invalid args. Input following cmds *-1), it's operate same as *-2)\n"\
		" * 1-1)$> ./pipex infile_name \"cmd1\" \"cmd2\" outfile_name\n"\
		"   1-2)$> < infile_name cmd1 | cmd2 > outfile_name\n"\
		" * 2-1)$> ./pipex here_doc LIMITER cmd1 cmd2 outfile_name\n"\
		"   2-2)$> cmd1 << LIMITER | cmd2 >> outfile_name", \
		NULL, EXIT_FAILURE, NULL);
	exit_status = -1;
	if (argc == 6)
	{
		here_doc_flg = ft_strtrim(argv[1], SPACES);
		if (!here_doc_flg)
			perror_and_exit_b("malloc", EXIT_FAILURE);
		if (ft_strncmp_ns(here_doc_flg, HERE_DOC, ft_strlen_ns(HERE_DOC)) == 0)
			exit_status = here_doc(argv);
		free(here_doc_flg);
	}
	if (exit_status == -1)
		exit_status = multi_pipe_controller(argc, argv);
	return (exit_status);
}

#ifdef LESKS

__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q pipex");
}

#endif
