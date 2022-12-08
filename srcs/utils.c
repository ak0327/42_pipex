/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:12:48 by takira            #+#    #+#             */
/*   Updated: 2022/12/06 20:12:50 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex.h"

/* functions */
void	free_allocs(char **alloc_array, char *alloc_str)
{
	size_t	i;

	i = 0;
	if (alloc_array)
		while (alloc_array[i])
			free(alloc_array[i++]);
	free(alloc_array);
	if (alloc_str)
		free(alloc_str);
}

void	free_and_ret_null(char **alloc_str)
{
	if (alloc_str)
		free(*alloc_str);
	*alloc_str = NULL;
}

void	close_and_frees(t_pipe *p)
{
	close(p->pipe_fd[READ]);
	close(p->pipe_fd[WRITE]);
	free_allocs(p->input_cmd1, p->path_cmd1);
	free_allocs(p->input_cmd2, p->path_cmd2);
	free_allocs(p->env_paths, NULL);
	free(p->infile_name);
	free(p->outfile_name);
}

void	perror_and_exit(char *err_str, int exit_no)
{
	perror(err_str);
	exit (exit_no);
}

void	errmsg_and_exit(char *errmsg, int exit_no)
{
	if (errmsg)
		ft_putendl_fd(errmsg, STDERR_FILENO);
	exit (exit_no);
}

void	exit_and_errmsg_cmd_not_found(char *cmd, int exit_no, t_pipe *p)
{
	p->exit_status = exit_no;
	ft_putstr_fd("[Error] command not found: ", STDERR_FILENO);
	ft_putendl_fd(cmd, STDERR_FILENO);
	debug_msg_str1_n_str2_nl("cmd_not_found exit_status:", p->exit_status, "");
	exit (p->exit_status);
}

/* for debug */
//FILE	*fp = fopen("print", "w");

void	fprint_2d_arr(char **array, char *info_str, FILE *fp)
{
	size_t	i;

	i = 0;
	if (info_str)
		fprintf(fp, "#print_2d_arr");
	fprintf(fp, " %s:[", info_str);
	while (array[i])
		fprintf(fp, "  '%s'\n", array[i++]);
	fprintf(fp, "]\n");
}

void	print_2d_arr(char **array, char *info_str)
{
	size_t	i;

	i = 0;
	if (info_str)
		printf("#print_2d_arr");
	printf(" %s:[\n", info_str);
	while (array[i])
		printf("  '%s'\n", array[i++]);
	printf("]\n");
}

void	debug_msg_str1_n_str2_nl(char *str1, int n, char *str2)
{
	ft_putstr_fd(str1, STDERR_FILENO);
	ft_putnbr_fd(n, STDERR_FILENO);
	ft_putstr_fd(str2, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
