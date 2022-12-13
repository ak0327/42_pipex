/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:51:23 by takira            #+#    #+#             */
/*   Updated: 2022/12/09 21:48:16 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex_bonu.h"

/* prototype declaration */
static t_cmd	*get_i_th_cmd_lst(t_pipe *p, size_t i_th);
static void		operate_fds_for_parent(int pipe_fd[2], int exit_fail_no, size_t pipe_no, t_pipe *p);
//static void		operate_fds_for_child(int pipe_fd[2], int exit_fail_no, size_t pipe_no, t_pipe *p);
static void		operate_fds_for_child(int pipe_fd[2], int exit_fail_no);
void	exec_i_th_pipe(t_pipe *p, int exit_fail_no, size_t pipe_no);

/* functions */

//int	pipe_parent(t_pipe *p, int exit_fail_no)
//{
//	int		pipe_fd[2];
//	pid_t	pid;
//	size_t	i;
//	int		status;
//
//	if (pipe(pipe_fd) < 0)
//		perror_and_exit_b("pipe", exit_fail_no);
//	pid = fork();
//	if (pid < 0)
//		perror_and_exit_b("fork", exit_fail_no);
//	if (pid == 0)
//	{
//		operate_fds_for_child(pipe_fd, exit_fail_no);
//		exec_i_th_pipe(p, exit_fail_no, p->s_cmd_cnt - 1);
//	}
//	operate_fds_for_parent(pipe_fd, exit_fail_no, p->s_cmd_cnt, p);
//	close(pipe_fd[READ]);
//	close(pipe_fd[WRITE]);
//	i = 0;
//	debug_msg_str1_n_str2_nl_b("cmd_cnd:", (int)p->s_cmd_cnt, "");
//	while (i < p->s_cmd_cnt)
//	{
////		wait(&status);
//		if (wait(&status) < 0)
//			perror("wait");
////			perror_and_exit_b("wait", exit_fail_no);
//		i++;
//	}
////	i = p->s_cmd_cnt + 1;
////	while (i--)
////		wait(&status);
//	return (WEXITSTATUS(status));
//}
int	pipe_parent(t_pipe *p, int exit_fail_no)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		perror_and_exit_b("fork", exit_fail_no);
	if (pid == 0)
		exec_i_th_pipe(p, exit_fail_no, p->s_cmd_cnt - 1);


//	if (waitpid(pid, &status, WUNTRACED) < 0)
//		perror("wait");
//	debug_msg_str1_n_str2_nl_b("wait childProcessCnt:", (int)p->child_process_cnt, "");

//	wait(&status);

	else
	{
		size_t	i;

		i = 0;
		while (i < p->s_cmd_cnt + 1)
		{
			wait(&status);
			i++;
		}

	}
	return (WEXITSTATUS(status));
}

void	exec_i_th_pipe(t_pipe *p, int exit_fail_no, size_t pipe_no)
{
	int		pipe_fd[2];
	t_cmd	*cmd_i;


	cmd_i = get_i_th_cmd_lst(p, pipe_no);
	if (!cmd_i)
		exit_with_msg_and_frees("Fail to get cmds", NULL, exit_fail_no, p);
	print_2d_arr_b(cmd_i->c_cmds, "cmd");
	if (pipe(pipe_fd) < 0)
		perror_and_exit_b("pipe", exit_fail_no);
	if (pipe_no == 0)
	{
		if (open_infile_or_here_doc(p) == FAIL)
			return ;
		operate_fds_for_parent(pipe_fd, exit_fail_no, pipe_no, p);
		exec_i_th_cmd(p, cmd_i, exit_fail_no);
		return ;
	}
	cmd_i->t_pid = fork();
	if (cmd_i->t_pid < 0)
		perror_and_exit_b("fork", exit_fail_no);
	if (cmd_i->t_pid == 0)
	{
		operate_fds_for_child(pipe_fd, exit_fail_no);
		exec_i_th_pipe(p, exit_fail_no, pipe_no - 1);
	}
	debug_msg_str1_n_str2_nl_b("pid:", cmd_i->t_pid, "");
//	waitpid(cmd_i->t_pid, NULL, 0);
	operate_fds_for_parent(pipe_fd, exit_fail_no, pipe_no, p);
	exec_i_th_cmd(p, cmd_i, exit_fail_no);

}

//void	exec_i_th_pipe(t_pipe *p, int exit_fail_no, size_t pipe_no)
//{
//	int		pipe_fd[2];
//	t_cmd	*cmd_i;
//
//	p->child_process_cnt++;
//	if (pipe_no == 0 && open_infile_or_here_doc(p) == FAIL)
//		return ;
//	cmd_i = get_i_th_cmd_lst(p, pipe_no);
//	if (!cmd_i)
//		exit_with_msg_and_frees("Fail to get cmds", NULL, exit_fail_no, p);
//	print_2d_arr_b(cmd_i->c_cmds, "cmd");
//	cmd_i->test = 100;
//	if (pipe(pipe_fd) < 0)
//		perror_and_exit_b("pipe", exit_fail_no);
//	if (pipe_no > 0)
//	{
//		cmd_i->t_pid = fork();
//		if (cmd_i->t_pid < 0)
//			perror_and_exit_b("fork", exit_fail_no);
//		if (cmd_i->t_pid == 0)
//		{
//			operate_fds_for_child(pipe_fd, exit_fail_no);
//			exec_i_th_pipe(p, exit_fail_no, pipe_no - 1);
//		}
//	}
//	debug_msg_str1_n_str2_nl_b("pid:", cmd_i->t_pid, "");
////	waitpid(cmd_i->t_pid, NULL, 0);
//	operate_fds_for_parent(pipe_fd, exit_fail_no, pipe_no, p);
//	exec_i_th_cmd(p, cmd_i, exit_fail_no);
//
//}

static t_cmd	*get_i_th_cmd_lst(t_pipe *p, size_t i_th)
{
	t_cmd	*i_th_cmd;
	t_list	*lst;
	size_t	lst_idx;

	lst_idx = 0;
	lst = p->t_cmd_list;
	while (lst && lst_idx < i_th)
	{
		lst = lst->next;
		lst_idx++;
	}
	if (!lst)
		return (NULL);
	i_th_cmd = lst->content;
	return (i_th_cmd);
}

static void	operate_fds_for_parent(int pipe_fd[2], int exit_fail_no, size_t pipe_no, t_pipe *p)
{
	if (close(pipe_fd[WRITE]) < 0)
		perror_and_exit_b("close", exit_fail_no);
	if (dup2(pipe_fd[READ], STDIN_FILENO) < 0)
		perror_and_exit_b("dup2", exit_fail_no);
	if (close(pipe_fd[READ]) < 0)
		perror_and_exit_b("close", exit_fail_no);
	if (pipe_no == 0 && !p->c_limiter)
	{
		if (dup2(p->i_file_fd[READ], STDIN_FILENO) < 0)
			perror_and_exit_b("dup2", exit_fail_no);
		if (close(p->i_file_fd[READ]) < 0)
			perror_and_exit_b("close", exit_fail_no);
	}
	if (pipe_no == 0 && p->c_limiter)
		ft_lstiter_fd(p->t_here_doc_contents, STDOUT_FILENO, ft_putstr_fd);
}

static void	operate_fds_for_child(int pipe_fd[2], int exit_fail_no)
{
	if (close(pipe_fd[READ]) < 0)
		perror_and_exit_b("close", exit_fail_no);
	if (dup2(pipe_fd[WRITE], STDOUT_FILENO) < 0)
		perror_and_exit_b("dup2", exit_fail_no);
	if (close(pipe_fd[WRITE]) < 0)
		perror_and_exit_b("close", exit_fail_no);
}

