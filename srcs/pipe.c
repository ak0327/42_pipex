/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:51:23 by takira            #+#    #+#             */
/*   Updated: 2022/12/06 19:51:24 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex.h"

/* prototype declaration */
static void	exec_cmd(t_pipe *p, t_cmd *cmd, int exit_fail_no);
static void	fd_dups(t_pipe *p, int fd_dup_for, int exit_fail_no);
static char	*create_cmd_path(char *env_path, const char *cmd);
static int	wait_pids(t_pipe *p, int exit_fail_no);

/* functions */
int	exec_pipe(t_pipe *p, int exit_fail_no)
{
	if (pipe(p->pipe_fd) < 0)
		exit_with_perror_free("pipe", exit_fail_no, p);
	if (open_infile(p) == PASS)
		exec_cmd(p, p->cmd1, exit_fail_no);
	if (open_outfile(p) == PASS)
		exec_cmd(p, p->cmd2, exit_fail_no);
	if (close(p->pipe_fd[READ]) < 0 || close(p->pipe_fd[WRITE]) < 0)
		exit_with_perror_free("close", exit_fail_no, p);
	if (p->cmd2->pid >= 0)
		p->exit_status = wait_pids(p, exit_fail_no);
	return (p->exit_status);
}

static void	exec_cmd(t_pipe *p, t_cmd *cmd, int exit_fail_no)
{
	size_t	i;

	cmd->pid = fork();
	if (cmd->pid < 0)
		exit_with_perror_free("fork", exit_fail_no, p);
	if (cmd->pid == 0)
	{
		fd_dups(p, cmd->fd_dup_for, exit_fail_no);
		if (cmd->is_rel || cmd->is_abs)
			execve(cmd->cmds[0], cmd->cmds, p->env);
		i = 0;
		while (!cmd->is_rel && !cmd->is_abs && cmd->cmds[0] && p->env_paths[i])
		{
			cmd->path = create_cmd_path(p->env_paths[i++], cmd->cmds[0]);
			if (!cmd->path)
				exit_with_errmsg_free("Fail to malloc", NULL, exit_fail_no, p);
			execve(cmd->path, cmd->cmds, p->env);
			free_1d_array(&cmd->path);
		}
		exit_with_errmsg_free(\
		"command not found", cmd->cmds[0], CMD_NOT_FOUND, p);
	}
}

static void	fd_dups(t_pipe *p, int fd_dup_for, int exit_fail_no)
{
	if (fd_dup_for == STDOUT_FILENO)
	{
		if (close(p->pipe_fd[READ]) < 0)
			exit_with_perror_free("close", exit_fail_no, p);
		if (dup2(p->pipe_fd[WRITE], STDOUT_FILENO) < 0)
			exit_with_perror_free("dup2", exit_fail_no, p);
		if (close(p->pipe_fd[WRITE]) < 0)
			exit_with_perror_free("close", exit_fail_no, p);
		if (dup2(p->file_fd[READ], STDIN_FILENO) < 0)
			exit_with_perror_free("dup2", exit_fail_no, p);
		if (close(p->file_fd[READ]) < 0)
			exit_with_perror_free("close", exit_fail_no, p);
		return ;
	}
	if (close(p->pipe_fd[WRITE]) < 0)
		exit_with_perror_free("close", exit_fail_no, p);
	if (dup2(p->pipe_fd[READ], STDIN_FILENO) < 0)
		exit_with_perror_free("dup2", exit_fail_no, p);
	if (close(p->pipe_fd[READ]) < 0)
		exit_with_perror_free("close", exit_fail_no, p);
	if (dup2(p->file_fd[WRITE], STDOUT_FILENO) < 0)
		exit_with_perror_free("dup2", exit_fail_no, p);
	if (close(p->file_fd[WRITE]) < 0)
		exit_with_perror_free("close", exit_fail_no, p);
}

static char	*create_cmd_path(char *env_path, const char *cmd)
{
	char			*cmd_path;
	const size_t	env_path_len = ft_strlen_ns(env_path);
	const size_t	cmd_len = ft_strlen_ns(cmd);

	if (!cmd)
		return (NULL);
	cmd_path = (char *)ft_calloc(sizeof(char), env_path_len + cmd_len + 2);
	if (!cmd_path)
		return (NULL);
	ft_strlcpy(cmd_path, env_path, env_path_len + 1);
	ft_strlcat(cmd_path, "/", env_path_len + 2);
	ft_strlcat(cmd_path, cmd, env_path_len + cmd_len + 2);
	return (cmd_path);
}

static int	wait_pids(t_pipe *p, int exit_fail_no)
{
	int	status1;
	int	status2;

	status1 = 0;
	status2 = 0;
	if (p->cmd1->pid >= 0 && waitpid(p->cmd1->pid, &status1, 0) < 0)
		exit_with_perror_free("waitpid", exit_fail_no, p);
	if (p->cmd2->pid >= 0 && waitpid(p->cmd2->pid, &status2, 0) < 0)
		exit_with_perror_free("waitpid", exit_fail_no, p);
	return (WEXITSTATUS(status2));
}
