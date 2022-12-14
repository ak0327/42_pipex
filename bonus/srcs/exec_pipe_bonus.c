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
static void		operate_fds_for_child(int pipe_fd[2], int exit_fail_no);
static void		operate_fds_for_parent(int pipe_fd[2], int exit_fail_no);
static void		connect_infile_or_here_doc_content(t_pipe *p, int exit_fail_no);

/* functions */
int	pipe_parent(t_pipe *p, int exit_fail_no)
{
	pid_t	pid;
	int		status;
	size_t	i;

	pid = fork();
	if (pid < 0)
		perror_and_exit_b("fork", exit_fail_no);
	if (pid == 0)
		exec_i_th_pipe(p, exit_fail_no, p->s_cmd_cnt - 1);
	i = 0;
	while (i++ < p->s_cmd_cnt + 1)
		wait(&status);
	return (WEXITSTATUS(status));
}

void	exec_i_th_pipe(t_pipe *p, int exit_fail_no, size_t pipe_no)
{
	int		pipe_fd[2];
	t_cmd	*cmd_i;

	cmd_i = get_i_th_cmd_lst(p, pipe_no);
	if (!cmd_i)
		exit_with_msg_and_frees("Fail to get cmds", NULL, exit_fail_no, p);
	if (pipe(pipe_fd) < 0)
		perror_and_exit_b("pipe", exit_fail_no);
	cmd_i->t_pid = fork();
	if (cmd_i->t_pid < 0)
		perror_and_exit_b("fork", exit_fail_no);
	if (cmd_i->t_pid == 0)
	{
		operate_fds_for_child(pipe_fd, exit_fail_no);
		if (pipe_no > 0)
			exec_i_th_pipe(p, exit_fail_no, pipe_no - 1);
		connect_infile_or_here_doc_content(p, exit_fail_no);
		exit (0);
	}
	operate_fds_for_parent(pipe_fd, exit_fail_no);
	exec_i_th_cmd(p, cmd_i, exit_fail_no);
}

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

static void	operate_fds_for_parent(int pipe_fd[2], int exit_fail_no)
{
	if (close(pipe_fd[WRITE]) < 0)
		perror_and_exit_b("close", exit_fail_no);
	if (close(STDIN_FILENO) < 0)
		perror_and_exit_b("close", exit_fail_no);
	if (dup2(pipe_fd[READ], STDIN_FILENO) < 0)
		perror_and_exit_b("dup2", exit_fail_no);
	if (close(pipe_fd[READ]) < 0)
		perror_and_exit_b("close", exit_fail_no);
}

static void	operate_fds_for_child(int pipe_fd[2], int exit_fail_no)
{
	if (close(pipe_fd[READ]) < 0)
		perror_and_exit_b("close", exit_fail_no);
	if (close(STDOUT_FILENO) < 0)
		perror_and_exit_b("close", exit_fail_no);
	if (dup2(pipe_fd[WRITE], STDOUT_FILENO) < 0)
		perror_and_exit_b("dup2", exit_fail_no);
	if (close(pipe_fd[WRITE]) < 0)
		perror_and_exit_b("close", exit_fail_no);
}

static void	connect_infile_or_here_doc_content(t_pipe *p, int exit_fail_no)
{
	ssize_t	read_byte;
	char	buf[BUF_SIZE];

	if (!p->c_limiter)
	{
		if (open_infile_b(p) == FAIL)
			return ;
		while (true)
		{
			read_byte = read(p->i_file_fd[READ], &buf, BUF_SIZE);
			if (read_byte <= 0)
				break ;
			ft_putstr_fd(buf, STDOUT_FILENO);
		}
		if (read_byte < 0)
			perror_and_exit_b("read", exit_fail_no);
	}
	if (p->c_limiter && p->is_here_doc_success)
		ft_lstiter_fd(p->t_here_doc_contents, STDOUT_FILENO, ft_putstr_fd);
}
