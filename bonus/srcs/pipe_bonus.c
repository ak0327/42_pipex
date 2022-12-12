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
static void	exec_cmd_b(t_pipe *p, t_cmd *cmd, int exit_num_if_fail);
static void	fd_dups_b(t_pipe *p, int fd_dup_for, int exit_num_if_fail);
static char	*create_cmd_path_b(char *env_path, const char *cmd);
static int	wait_pids_b(t_pipe *p, int exit_num_if_fail);

/* functions */
int	exec_pipe_b(t_pipe *p, int exit_num_if_fail)
{
	if (pipe(p->pipe_fd) < 0)
		perror_and_exit_b("pipe", exit_num_if_fail);
	if (open_infile_b(p) == PASS)
		exec_cmd_b(p, p->cmd1, exit_num_if_fail);
	if (open_outfile_b(p) == PASS)
		exec_cmd_b(p, p->cmd2, exit_num_if_fail);
	if (close(p->pipe_fd[READ]) < 0 || close(p->pipe_fd[WRITE]) < 0)
		perror_and_exit_b("close", exit_num_if_fail);
	if (p->cmd2->pid >= 0)
		p->exit_status = wait_pids_b(p, exit_num_if_fail);
	return (p->exit_status);
}

static void	exec_cmd_b(t_pipe *p, t_cmd *cmd, int exit_num_if_fail)
{
	size_t	i;

	cmd->pid = fork();
	if (cmd->pid < 0)
		perror_and_exit_b("fork", exit_num_if_fail);
	if (cmd->pid == 0)
	{
		fd_dups_b(p, cmd->fd_dup_for, exit_num_if_fail);
		if (cmd->is_rel || cmd->is_abs)
			execve(cmd->cmds[0], cmd->cmds, p->env);
		i = 0;
		while (!cmd->is_rel && !cmd->is_abs && cmd->cmds[0] && p->env_paths[i])
		{
			cmd->path = create_cmd_path_b(p->env_paths[i++], cmd->cmds[0]);
			if (!cmd->path)
				perror_and_exit_b("malloc", exit_num_if_fail);
			execve(cmd->path, cmd->cmds, p->env);
			free_and_ret_null_b(&cmd->path);
		}
		errmsg_str1_str2_exit_b(\
		"command not found", cmd->cmds[0], CMD_NOT_FOUND);
	}
}

static void	fd_dups_b(t_pipe *p, int fd_dup_for, int exit_num_if_fail)
{
	if (fd_dup_for == STDOUT_FILENO)
	{
		if (close(p->pipe_fd[READ]) < 0)
			perror_and_exit_b("close", exit_num_if_fail);
		if (dup2(p->pipe_fd[WRITE], STDOUT_FILENO) < 0)
			perror_and_exit_b("dup2", exit_num_if_fail);
		if (close(p->pipe_fd[WRITE]) < 0)
			perror_and_exit_b("close", exit_num_if_fail);
		if (dup2(p->file_fd[READ], STDIN_FILENO) < 0)
			perror_and_exit_b("dup2", exit_num_if_fail);
		if (close(p->file_fd[READ]) < 0)
			perror_and_exit_b("close", exit_num_if_fail);
		return ;
	}
	if (close(p->pipe_fd[WRITE]) < 0)
		perror_and_exit_b("close", exit_num_if_fail);
	if (dup2(p->pipe_fd[READ], STDIN_FILENO) < 0)
		perror_and_exit_b("dup2", exit_num_if_fail);
	if (close(p->pipe_fd[READ]) < 0)
		perror_and_exit_b("close", exit_num_if_fail);
	if (dup2(p->file_fd[WRITE], STDOUT_FILENO) < 0)
		perror_and_exit_b("dup2", exit_num_if_fail);
	if (close(p->file_fd[WRITE]) < 0)
		perror_and_exit_b("close", exit_num_if_fail);
}

static char	*create_cmd_path_b(char *env_path, const char *cmd)
{
	char			*cmd_path;
	const size_t	env_path_len = ft_strlen_ns(env_path);
	const size_t	cmd_len = ft_strlen_ns(cmd);

	if (!cmd)
		return (NULL);
	cmd_path = (char *)malloc(sizeof(char) * (env_path_len + cmd_len + 2));
	if (!cmd_path)
		return (NULL);
	ft_strlcpy(cmd_path, env_path, env_path_len + 1);
	ft_strlcat(cmd_path, "/", env_path_len + 2);
	ft_strlcat(cmd_path, cmd, env_path_len + cmd_len + 2);
	return (cmd_path);
}

static int	wait_pids_b(t_pipe *p, int exit_num_if_fail)
{
	int	status1;
	int	status2;

	status1 = 0;
	status2 = 0;
	if (p->cmd1->pid >= 0 && waitpid(p->cmd1->pid, &status1, 0) < 0)
		perror_and_exit_b("waitpid", exit_num_if_fail);
	if (p->cmd2->pid >= 0 && waitpid(p->cmd2->pid, &status2, 0) < 0)
		perror_and_exit_b("waitpid", exit_num_if_fail);
	return (WEXITSTATUS(status2));
}
