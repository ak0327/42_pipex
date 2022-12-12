/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 21:15:50 by takira            #+#    #+#             */
/*   Updated: 2022/12/10 21:15:52 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex_bonu.h"

int	is_last_line_eof(char *line, char *limiter)
{
	const size_t	line_len = ft_strlen_ns(line);
	const size_t	limiter_len = ft_strlen_ns(limiter);
	int		cmp_res;

	if (!line || !limiter)
		return (FAIL);
	cmp_res = ft_strncmp_ns(line, limiter, limiter_len);
	if (line_len == limiter_len + 1 && cmp_res == 0)
		return (PASS);
	return (FAIL);
}

int	get_contents_to_lst(t_list *ptr, char *limiter, bool *is_eof)
{
	char	*line;
	t_list	*new_node;

	while (true)
	{
		ft_putstr_fd("heredoc>", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO, true);
		if (!line)
			return (FAIL);
		if (ft_strncmp(line, limiter, strlen(limiter)) == 0)
			break ;
		line = expansion_env_variable(line);
		new_node = ft_lstnew(line);
		ft_lstadd_back(&ptr, new_node);
	}
	if (is_last_line_eof(line, limiter) == true)
		*is_eof = true;
	else
	{
		*is_eof = false;
		free(line);
	}
	return (PASS);
}

//int	pass_contents_to_next_fd(int next_fd)
//{
//
//
//}

// ./pipex  here_doc  LIMITER  cmd1  cmd2  outfile
// -> argc == 6 && argv[1] == "here_doc"

int here_doc(char **argv)
{
//	char	*line;
//	int		file_fd[2];
//	char	*outfile_name = "file1";
//	t_list	*ptr;
//	bool	is_eof;

	t_pipe	p;
	int		exit_status;
	char	*limiter;
	//init
	printf("## here_doc ##\n");

	limiter = ft_strtrim(argv[2], SPACES);
	if (!limiter)
		exit (1);
	printf("limiter:[%s]\n", limiter);
	init_pipe_params_b(&p, &argv, 2, limiter);

	//get input
	get_env_paths_b(&p, EXIT_FAILURE);
	get_input_cmds(&p, EXIT_FAILURE);
	get_file_names_b(&p, EXIT_FAILURE);

	// do here_doc & pipe & update exit status
	exit_status = EXIT_SUCCESS;

	// free


//	limiter = ft_strtrim(argv[2], SPACES);
//	if (!limiter)
//		exit_with_msg_and_free_allocs("Fail to get LIMITER", NULL, EXIT_FAILURE);
//	ptr = NULL;
//	if (get_contents_to_lst(ptr, limiter, &is_eof) == FAIL)
//	{
//		ft_lstclear(&ptr, free);
//		exit_with_msg_and_free_allocs("Fail to get here_doc", NULL,
//									  EXIT_FAILURE);
//	}
//	if (is_last_line_eof(line, limiter) == PASS)
//	{
//		file_fd[WRITE] = file_open_for(outfile_name, FILE_APPEND);
//		if (file_fd[WRITE] < 0)
//			exit (2);
//
//		ft_lstiter_fd(ptr, file_fd[WRITE], ft_putstr_fd);
//
//		if (close(file_fd[WRITE]) < 0)
//			exit (3);
//	}
//
//	free(line);
//	ft_lstclear(&ptr, free);
//
//	system("leaks -q a.out");
	return (exit_status);
}