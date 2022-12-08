/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:46:36 by takira            #+#    #+#             */
/*   Updated: 2022/12/08 16:46:37 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex.h"

void	recursion_pipe(int cmd_no, t_pipe *p, int exit_no_if_fail)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (cmd_no == p->num_of_cmds)
	{
		// cmd1
		// error msg
		return ;
	}
	if (pipe(pipe_fd) < 0)
		perror_and_exit("pipe", exit_no_if_fail);
	pid = fork();
	if (pid < 0)
		perror_and_exit("fork", exit_no_if_fail);
	if (pid == 0)
	{
		close(pipe_fd[READ]);
		dup2(pipe_fd[WRITE], STDOUT_FILENO);
		close(pipe_fd[WRITE]);
		recursion_pipe(cmd_no + 1, p, exit_no_if_fail);
	}
	close(pipe_fd[WRITE]);
	dup2(pipe_fd[READ], STDIN_FILENO);
	close(pipe_fd[READ]);
}

void	exec_pipes(t_pipe *p, int exit_no_if_fail)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror_and_exit("fork", exit_no_if_fail);
	if (pid == 0)
		recursion_pipe(0, p, exit_no_if_fail);
	if (waitpid(pid, NULL, 0) < 0)
		perror_and_exit("wait", exit_no_if_fail);
}
