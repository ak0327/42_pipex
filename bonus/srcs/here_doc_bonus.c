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

/* prototype declaration */
static int	is_last_line_eof(char *line, char *limiter);
static int	get_here_doc_contents_to_lst(t_pipe *p);

/* functions */
bool	get_here_doc(t_pipe *p)
{
	if (get_here_doc_contents_to_lst(p) == FAIL)
	{
		errmsg_str1_str2_b("Error occurred", "here_doc");
		return (false);
	}
	return (true);
}

static int	get_here_doc_contents_to_lst(t_pipe *p)
{
	char	*line;
	t_list	*envs;
	t_list	*new_node;
	int		is_here_doc_success;

	envs = get_env_lst(p, EXIT_FAILURE);
	is_here_doc_success = FAIL;
	while (true)
	{
		ft_putstr_fd("heredoc>", STDIN_FILENO);
		line = get_next_line(STDIN_FILENO, true);
		if (!line)
			return (FAIL);
		if (ft_strncmp_ns(line, p->c_limiter, ft_strlen_ns(p->c_limiter)) == 0)
			break ;
		line = expansion_env_variable(line, envs);
		new_node = ft_lstnew(line);
		ft_lstadd_back(&p->t_here_doc_contents, new_node);
	}
	if (is_last_line_eof(line, p->c_limiter) == true)
		is_here_doc_success = PASS;
	free(line);
	ft_lstclear(&envs, free_env_elem);
	return (is_here_doc_success);
}

static int	is_last_line_eof(char *line, char *limiter)
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
