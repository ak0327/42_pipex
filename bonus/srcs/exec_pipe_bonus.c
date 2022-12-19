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

#include "./../includes/pipex_bonus.h"

/* prototype declaration */
static t_cmd	*get_i_th_cmd_lst(t_pipe *p, size_t i_th);
static void		operate_child_fds(int pipe_fd[2], int exit_fail_no, t_pipe *p);
static void		operate_parent_fds(int pipe_fd[2], int exit_no, t_pipe *p);
static void		connect_infile_or_heredoc_content(t_pipe *p, int exit_fail_no);

/* functions */
void	exec_i_th_pipe(t_pipe *p, int exit_fail_no, size_t pipe_no)
{
	int		pipe_fd[2];
	t_cmd	*cmd_i;

	cmd_i = get_i_th_cmd_lst(p, pipe_no);
	if (!cmd_i)
		exit_with_errmsg_and_free_b("Fail to get cmds", NULL, exit_fail_no, p);
	if (pipe(pipe_fd) < 0)
		exit_with_perror_free_b("pipe", exit_fail_no, p);
	if (pipe_no > 0)
	{
		cmd_i->t_pid = fork();
		if (cmd_i->t_pid < 0)
			exit_with_perror_free_b("fork", exit_fail_no, p);
		if (cmd_i->t_pid == 0)
		{
			operate_child_fds(pipe_fd, exit_fail_no, p);
			exec_i_th_pipe(p, exit_fail_no, pipe_no - 1);
		}
	}
	operate_parent_fds(pipe_fd, exit_fail_no, p);
	if (pipe_no == 0)
		connect_infile_or_heredoc_content(p, exit_fail_no);
	exec_i_th_cmd(p, cmd_i, exit_fail_no);
}

static t_cmd	*get_i_th_cmd_lst(t_pipe *p, size_t i_th)
{
	t_cmd	*i_th_cmd;
	t_list	*lst;
	size_t	lst_idx;

	lst_idx = 0;
	lst = p->t_cmd_list_m;
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

static void	operate_parent_fds(int pipe_fd[2], int exit_no, t_pipe *p)
{
	if (close(pipe_fd[WRITE]) < 0)
		exit_with_perror_free_b("close", exit_no, p);
	if (close(STDIN_FILENO) < 0)
		exit_with_perror_free_b("close", exit_no, p);
	if (dup2(pipe_fd[READ], STDIN_FILENO) < 0)
		exit_with_perror_free_b("dup2", exit_no, p);
	if (close(pipe_fd[READ]) < 0)
		exit_with_perror_free_b("close", exit_no, p);
}

static void	operate_child_fds(int pipe_fd[2], int exit_fail_no, t_pipe *p)
{
	if (close(pipe_fd[READ]) < 0)
		exit_with_perror_free_b("close", exit_fail_no, p);
	if (close(STDOUT_FILENO) < 0)
		exit_with_perror_free_b("close", exit_fail_no, p);
	if (dup2(pipe_fd[WRITE], STDOUT_FILENO) < 0)
		exit_with_perror_free_b("dup2", exit_fail_no, p);
	if (close(pipe_fd[WRITE]) < 0)
		exit_with_perror_free_b("close", exit_fail_no, p);
}

static void	connect_infile_or_heredoc_content(t_pipe *p, int exit_fail_no)
{
	if (!p->c_limiter_m)
	{
		if (open_infile_b(p) == FAIL)
			return ;
		if (dup2(p->i_file_fd[READ], STDIN_FILENO) < 0)
			exit_with_perror_free_b("dup2", exit_fail_no, p);
		if (close(p->i_file_fd[READ]) < 0)
			exit_with_perror_free_b("close", exit_fail_no, p);
	}
	if (p->c_limiter_m)
		ft_lstiter_fd(p->t_here_doc_contents, STDOUT_FILENO, ft_putstr_fd);
}
