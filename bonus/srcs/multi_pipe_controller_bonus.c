/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:40:09 by takira            #+#    #+#             */
/*   Updated: 2022/12/12 18:40:11 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex_bonu.h"

/* prototype declaration */
//static int	wait_children(t_pipe *p, int exit_fail_no);

/* functions */
int	multi_pipe_controller(t_pipe *p, int exit_fail_no)
{
	if (open_outfile_b(p) == FAIL)
		return (exit_fail_no);
	if (dup2(p->i_file_fd[WRITE], STDOUT_FILENO) < 0)
		perror_and_exit_b("dup2", exit_fail_no);
	if (close(p->i_file_fd[WRITE]) < 0)
		perror_and_exit_b("close", exit_fail_no);
	p->i_exit_status = pipe_parent(p, exit_fail_no);
	debug_msg_str1_n_str2_nl_b("controller childProcessCnt:", (int)p->child_process_cnt, "");
//	t_list	*lst;
//	t_cmd	*cmd;
//	lst = p->t_cmd_list;
//	while (lst->next)
//	{
//		cmd = lst->content;
//		debug_msg_str1_n_str2_nl_b("wait pid:", cmd->t_pid, "");
//		debug_msg_str1_n_str2_nl_b("wait test:", cmd->test, "");
//		if (waitpid(cmd->t_pid, NULL, WUNTRACED) < 0)
//			perror("wait");
//		lst = lst->next;
//	}

//	exec_i_th_pipe(p, exit_fail_no, p->s_cmd_cnt - 1);
//	p->i_exit_status = wait_children(p, exit_fail_no);
	return (p->i_exit_status);
}

//static int	wait_children(t_pipe *p, int exit_fail_no)
//{
//	size_t	i;
//	int		status;
//
//	i = 0;
//	while (i <= p->s_cmd_cnt)
//	{
//		if (wait(&status) < 0)
//			perror_and_exit_b("wait", exit_fail_no);
//		i++;
//	}
////	exit_fail_no++;
////	i = p->s_cmd_cnt;
////	while (i--)
////		wait(&status);
//
//	return (WEXITSTATUS(status));
//}
