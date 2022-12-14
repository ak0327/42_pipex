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

#include "./../includes/pipex_bonus.h"

/* prototype declaration */
static int	check_is_eof(char *line, char *limiter);

/* functions */
int	get_heredoc_contents_to_lst(t_pipe *p)
{
	char			*line_m;
	t_list			*envs_m;
	t_list			*new_node_m;
	int				is_here_doc_success;
	const size_t	limiter_len = ft_strlen_ns(p->c_limiter_m);

	envs_m = get_env_lst(p, EXIT_FAILURE);
	is_here_doc_success = FAIL;
	while (true)
	{
		ft_putstr_fd("heredoc>", STDIN_FILENO);
		line_m = get_next_line(STDIN_FILENO, true);
		if (line_m && ft_strncmp_ns(line_m, p->c_limiter_m, limiter_len) == 0)
			break ;
		line_m = expand_env_var_controller(line_m, envs_m);
		if (!line_m)
			break ;
		new_node_m = ft_lstnew(line_m);
		ft_lstadd_back(&p->t_here_doc_contents, new_node_m);
	}
	if (check_is_eof(line_m, p->c_limiter_m) == PASS)
		is_here_doc_success = PASS;
	free(line_m);
	ft_lstclear(&envs_m, free_env_elems);
	return (is_here_doc_success);
}

static int	check_is_eof(char *line, char *limiter)
{
	const size_t	line_len = ft_strlen_ns(line);
	const size_t	limiter_len = ft_strlen_ns(limiter);
	int				cmp_res;

	if (!line || !limiter)
		return (FAIL);
	cmp_res = ft_strncmp_ns(line, limiter, limiter_len);
	if (line_len == limiter_len + 1 && cmp_res == 0)
		return (PASS);
	return (FAIL);
}
