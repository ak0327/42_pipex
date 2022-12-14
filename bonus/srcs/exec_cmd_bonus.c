/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:21:42 by takira            #+#    #+#             */
/*   Updated: 2022/12/13 15:21:44 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex_bonus.h"

/* prototype declaration */
static char	*create_cmd_path_b(char *path_i, const char *cmd);

/* functions */
void	exec_i_th_cmd(t_pipe *p, t_cmd *cmd, int exit_fail_no)
{
	size_t	i;

	if (cmd->is_rel || cmd->is_abs)
		execve(cmd->c_cmds_m[0], cmd->c_cmds_m, p->c_environ);
	i = 0;
	while (!cmd->is_rel && !cmd->is_abs && cmd->c_cmds_m[0] && p->c_paths_m[i])
	{
		cmd->c_path_m = create_cmd_path_b(p->c_paths_m[i++], cmd->c_cmds_m[0]);
		if (!cmd->c_path_m)
			exit_with_perror_free_b("malloc", exit_fail_no, p);
		execve(cmd->c_path_m, cmd->c_cmds_m, p->c_environ);
		free_1d_array_b(&cmd->c_path_m);
	}
	exit_with_errmsg_and_free_b(\
	"command not found", cmd->c_cmds_m[0], CMD_NOT_FOUND, p);
}

static char	*create_cmd_path_b(char *path_i, const char *cmd)
{
	char			*cmd_path_m;
	const size_t	path_i_len = ft_strlen_ns(path_i);
	const size_t	cmd_len = ft_strlen_ns(cmd);

	if (!cmd)
		return (NULL);
	cmd_path_m = (char *)ft_calloc(sizeof(char), path_i_len + cmd_len + 2);
	if (!cmd_path_m)
		return (NULL);
	ft_strlcpy(cmd_path_m, path_i, path_i_len + 1);
	ft_strlcat(cmd_path_m, "/", path_i_len + 2);
	ft_strlcat(cmd_path_m, cmd, path_i_len + cmd_len + 2);
	return (cmd_path_m);
}
