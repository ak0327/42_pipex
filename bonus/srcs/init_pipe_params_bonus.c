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

#include "./../includes/pipex_bonus.h"

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
		cmd_cnt = CMD_CNT_HERE_DOC;
		is_here_doc = true;
	}
	if (init_p_param_b(p, argv, cmd_cnt, is_here_doc) == FAIL)
		exit_with_perror_free_b("malloc", EXIT_FAILURE, p);
	get_env_paths_b(p, exit_fail_no);
	get_input_cmds(p, exit_fail_no);
	get_file_names_b(p, exit_fail_no);
	if (is_here_doc && get_heredoc_contents_to_lst(p) == FAIL)
		exit_with_errmsg_and_free_b(\
		"Error occurred", "here_doc", exit_fail_no, p);
}

static int	init_p_param_b(t_pipe *p, char ***argv, size_t cmd_cnt, bool is_hd)
{
	extern char	**environ;

	if (!p || !argv || !*argv)
		return (FAIL);
	p->c_argv = *argv;
	p->c_environ = environ;
	p->c_paths_m = NULL;
	p->c_infile_name_m = NULL;
	p->c_outfile_name_m = NULL;
	p->c_limiter_m = NULL;
	p->i_exit_status = EXIT_SUCCESS;
	p->t_cmd_list_m = NULL;
	p->t_here_doc_contents = NULL;
	p->s_cmd_cnt = cmd_cnt;
	p->s_first_cmd_idx_in_argv = CMD_IDX_MULTI_PIPE;
	if (is_hd)
	{
		p->s_first_cmd_idx_in_argv = CMD_IDX_HERE_DOC;
		p->c_limiter_m = (*argv)[LIMITER_IDX];
		if (!p->c_limiter_m)
			return (FAIL);
	}
	return (PASS);
}

static int	check_here_doc_flg(char *argv1)
{
	char			*here_doc_flg_m;
	int				result;
	int				cmp_res;
	const size_t	here_doc_len = ft_strlen_ns(HERE_DOC_FLG);

	result = FAIL;
	here_doc_flg_m = ft_strtrim(argv1, SPACES);
	if (!here_doc_flg_m)
		exit_with_perror_free_b("malloc", EXIT_FAILURE, NULL);
	cmp_res = ft_strncmp_ns(here_doc_flg_m, HERE_DOC_FLG, here_doc_len);
	if (cmp_res == 0)
		result = PASS;
	free(here_doc_flg_m);
	return (result);
}
