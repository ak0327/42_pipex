/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe_params_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:41:06 by takira            #+#    #+#             */
/*   Updated: 2022/12/12 18:41:08 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex_bonu.h"

/* prototype declaration */
static int	check_here_doc_flg(char *argv1);
static int	init_p_param_b(t_pipe *p, char ***argv, size_t cmd_cnt, bool is_hd);

/* functions */
void	init_controller(t_pipe *p, int argc, char ***argv, int exit_fail_no)
{
	bool	is_here_doc;
	int		cmd_cnt;

	is_here_doc = false;
	cmd_cnt = argc - 3;
	if (argc == 6 && check_here_doc_flg((*argv)[1]) == PASS)
	{
		cmd_cnt = 2;
		is_here_doc = true;
	}
	if (init_p_param_b(p, argv, cmd_cnt, is_here_doc) == FAIL)
		perror_and_exit_b("malloc", EXIT_FAILURE);
	get_env_paths_b(p, exit_fail_no);
	get_input_cmds(p, exit_fail_no);
	get_file_names_b(p, exit_fail_no);
	if (is_here_doc)
		p->is_here_doc_success = get_here_doc(p);
}

static int	init_p_param_b(t_pipe *p, char ***argv, size_t cmd_cnt, bool is_hd)
{
	extern char	**environ;

	if (!p || !argv || !*argv)
		return (FAIL);
	p->c_argv = *argv;
	p->c_environ = environ;
	p->c_paths = NULL;
	p->c_infile_name = NULL;
	p->c_outfile_name = NULL;
	p->c_limiter = NULL;
	p->i_exit_status = EXIT_SUCCESS;
	p->t_cmd_list = NULL;
	p->t_here_doc_contents = NULL;
	p->s_cmd_cnt = cmd_cnt;
	p->s_first_cmd_idx_in_argv = CMD_IDX_MULTI_PIPE;
	p->is_here_doc_success = false;
	if (is_hd)
	{
		p->s_first_cmd_idx_in_argv = CMD_IDX_HERE_DOC;
		p->c_limiter = ft_strtrim((*argv)[LIMITER_IDX], SPACES);
		if (!p->c_limiter)
			return (FAIL);
	}
	return (PASS);
}

static int	check_here_doc_flg(char *argv1)
{
	char			*here_doc_flg;
	int				result;
	int				cmp_res;
	const size_t	here_doc_len = ft_strlen_ns(HERE_DOC_FLG);

	result = FAIL;
	here_doc_flg = ft_strtrim(argv1, SPACES);
	if (!here_doc_flg)
		perror_and_exit_b("malloc", EXIT_FAILURE);
	cmp_res = ft_strncmp_ns(here_doc_flg, HERE_DOC_FLG, here_doc_len);
	if (cmp_res == 0)
		result = PASS;
	free(here_doc_flg);
	return (result);
}
