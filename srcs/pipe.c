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
static void	child_for_cmd1(t_pipe *p, int exit_no_if_fail);
static void	child_for_cmd2(t_pipe *p, int exit_no_if_fail);
static char	*create_cmd_path(char *env_path, const char *cmd);
static void	wait_pids(t_pipe *p, int exit_no_if_fail);

/* functions */
void	exec_pipe(t_pipe *p, int exit_no_if_fail)
{
	if (pipe(p->pipe_fd) < 0)
		perror_and_exit("pipe", exit_no_if_fail);
	child_for_cmd1(p, exit_no_if_fail);
	child_for_cmd2(p, exit_no_if_fail);
	close(p->pipe_fd[READ]);
	close(p->pipe_fd[WRITE]);
	free_allocs(p);
	wait_pids(p, exit_no_if_fail);
}

static void	child_for_cmd1(t_pipe *p, int exit_no_if_fail)
{
	size_t	i;

	p->pid1 = fork();
	if (p->pid1 < 0)
		perror_and_exit("fork", exit_no_if_fail);
	if (p->pid1 == 0)
	{
		open_infile(p, exit_no_if_fail);
		close(p->pipe_fd[READ]);
		if (dup2(p->pipe_fd[WRITE], STDOUT_FILENO) < 0)
			perror_and_exit("dup2", exit_no_if_fail);
		close(p->pipe_fd[WRITE]);
		if (p->is_cmd1_relative)
			execve(p->input_cmd1[0], p->input_cmd1, p->env);
		i = 0;
		while (!p->is_cmd1_relative && p->input_cmd1[0] && p->env_paths[i])
		{
			p->path_cmd1 = create_cmd_path(p->env_paths[i++], p->input_cmd1[0]);
			if (!p->path_cmd1)
				errmsg_str1_str2_exit("Fail to malloc", NULL, exit_no_if_fail);
			execve(p->path_cmd1, p->input_cmd1, p->env);
			free_and_ret_null(&p->path_cmd1);
		}
		errmsg_str1_str2_exit("command not found", p->input_cmd1[0], 127);
	}
	exit (EXIT_SUCCESS);
}

static void	child_for_cmd2(t_pipe *p, int exit_no_if_fail)
{
	size_t	i;

	p->pid2 = fork();
	if (p->pid2 < 0)
		perror_and_exit("fork", exit_no_if_fail);
	if (p->pid2 == 0)
	{
		open_outfile(p, exit_no_if_fail);
		close(p->pipe_fd[WRITE]);
		if (dup2(p->pipe_fd[READ], STDIN_FILENO) < 0)
			perror_and_exit("dup2", exit_no_if_fail);
		close(p->pipe_fd[READ]);
		if (p->is_cmd2_relative)
			execve(p->input_cmd2[0], p->input_cmd2, p->env);
		i = 0;
		while (!p->is_cmd2_relative && p->input_cmd2[0] && p->env_paths[i])
		{
			p->path_cmd2 = create_cmd_path(p->env_paths[i++], p->input_cmd2[0]);
			if (!p->path_cmd2)
				errmsg_str1_str2_exit("Fail to malloc", NULL, exit_no_if_fail);
			execve(p->path_cmd2, p->input_cmd2, p->env);
			free_and_ret_null(&p->path_cmd2);
		}
		errmsg_str1_str2_exit("command not found", p->input_cmd2[0], 127);
	}
	exit (EXIT_SUCCESS);
}

static char	*create_cmd_path(char *env_path, const char *cmd)
{
	char			*cmd_path;
	const char		*trimmed_cmd = ft_strtrim(cmd, "/");
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

static void	wait_pids(t_pipe *p, int exit_no_if_fail)
{
	int	status1;
	int	status2;

	status1 = 0;
	status2 = 0;
	if (waitpid(p->pid1, &status1, 0) < 0 || waitpid(p->pid2, &status2, 0) < 0)
		perror_and_exit("waitpid", exit_no_if_fail);
	p->exit_status = status2 % 255;
}