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
static void	child_for_cmd1(t_pipe *p, int fail_exit_no);
static void	child_for_cmd2(t_pipe *p, int fail_exit_no);
static char	*create_cmd_path(char *env_path, const char *cmd);
static void	wait_pids(t_pipe *p, int fail_exit_no);

/* functions */
void	exec_pipe(t_pipe *p, int fail_exit_no)
{
	if (pipe(p->pipe_fd) < 0)
		perror_and_exit("pipe", fail_exit_no);
	child_for_cmd1(p, fail_exit_no);
	child_for_cmd2(p, fail_exit_no);
	close_and_frees(p);
	wait_pids(p, fail_exit_no);
}

static void	child_for_cmd1(t_pipe *p, int fail_exit_no)
{
	size_t	i;

	p->pid1 = fork();
	if (p->pid1 < 0)
		perror_and_exit("fork", fail_exit_no);
	if (p->pid1 == 0)
	{
		if (dup2(p->pipe_fd[WRITE], STDOUT_FILENO) < 0)
			perror_and_exit("dup2", fail_exit_no);
		close(p->pipe_fd[READ]);
		close(p->pipe_fd[WRITE]);
		i = 0;
		while (p->env_paths[i])
		{
			p->cmd_path1 = create_cmd_path(p->env_paths[i++], p->input_cmd1[0]);
			if (!p->cmd_path1)
				errmsg_and_exit("[Error] Fail to get cmd1 path", fail_exit_no);
			execve(p->cmd_path1, p->input_cmd1, p->env);
			free(p->cmd_path1);
		}
		perror_and_exit("execve", fail_exit_no);
	}
}

static void	child_for_cmd2(t_pipe *p, int fail_exit_no)
{
	size_t	i;

	p->pid2 = fork();
	if (p->pid2 < 0)
		perror_and_exit("fork", fail_exit_no);
	if (p->pid2 == 0)
	{
		if (dup2(p->pipe_fd[READ], STDIN_FILENO) < 0)
			perror_and_exit("dup2", fail_exit_no);
		close(p->pipe_fd[READ]);
		close(p->pipe_fd[WRITE]);
		i = 0;
		while (p->env_paths[i])
		{
			p->cmd_path2 = create_cmd_path(p->env_paths[i++], p->input_cmd2[0]);
			if (!p->cmd_path2)
				errmsg_and_exit("[Error] Fail to get cmd2 path", fail_exit_no);
			execve(p->cmd_path2, p->input_cmd2, p->env);
			free(p->cmd_path2);
		}
		perror_and_exit("execve", fail_exit_no);
	}
}

static char	*create_cmd_path(char *env_path, const char *cmd)
{
	char			*cmd_path;
	const char		*trimmed_cmd = ft_strtrim(cmd, "./");
	const size_t	env_path_len = ft_strlen_ns(env_path);
	const size_t	cmd_len = ft_strlen_ns(trimmed_cmd);

	if (!trimmed_cmd)
		return (NULL);
	cmd_path = (char *)malloc(sizeof(char) * (env_path_len + cmd_len + 2));
	if (!cmd_path)
		return (NULL);
	ft_strlcpy(cmd_path, env_path, env_path_len + 1);
	ft_strlcat(cmd_path, "/", env_path_len + 2);
	ft_strlcat(cmd_path, trimmed_cmd, env_path_len + cmd_len + 2);
	return (cmd_path);
}

static void	wait_pids(t_pipe *p, int fail_exit_no)
{
	if (waitpid(p->pid1, NULL, 0) < 0 || waitpid(p->pid2, NULL, 0) < 0)
		perror_and_exit("waitpid", fail_exit_no);
}
