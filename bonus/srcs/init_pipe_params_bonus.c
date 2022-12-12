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

// struct, 型がわかりにくい　命名で工夫してみる
void	init_pipe_params_b(t_pipe *p, char ***argv, size_t cmd_cnt, char *eof)
{
	extern char	**environ;

	p->c_argv = *argv;
	p->c_env = environ;
	p->c_env_paths = NULL;
	p->c_infile_name = NULL;
	p->c_outfile_name = NULL;
	p->c_limiter = eof;
	p->i_exit_status = EXIT_SUCCESS;
	p->t_cmd_list = NULL;
	p->s_cmd_cnt = cmd_cnt;
	if (eof)
		p->s_first_cmd_idx_in_argv = 3;
	else
		p->s_first_cmd_idx_in_argv = 2;
}


// argv -> make cmd_lst
//void	init_cmd_params_b(t_pipe *p, size_t cmd_cnt, size_t cmd1_idx_in_argv)
//{
//
//
//
//	p->cmd1 = (t_cmd *)malloc(sizeof(t_cmd));
//	p->cmd2 = (t_cmd *)malloc(sizeof(t_cmd));
//	if (!p->cmd1 || !p->cmd2)
//	{
//		free_allocs_b(p);
//		exit_with_msg_and_free_allocs("Fail to malloc", "", EXIT_FAILURE);
//	}
//	p->cmd1->cmds = NULL;
//	p->cmd2->cmds = NULL;
//	p->cmd1->path = NULL;
//	p->cmd2->path = NULL;
//	p->cmd1->is_rel = false;
//	p->cmd2->is_rel = false;
//	p->cmd1->is_abs = false;
//	p->cmd2->is_abs = false;
//	p->cmd1->fd_dup_for = STDOUT_FILENO;
//	p->cmd2->fd_dup_for = STDIN_FILENO;
//	p->cmd1->pid = -1;
//	p->cmd2->pid = -1;
//}
