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

void	close_and_frees(t_pipe *p)
{
	close(p->pipe_fd[READ]);
	close(p->pipe_fd[WRITE]);
	free_allocs(p->input_cmd1, p->cmd_path1);
	free_allocs(p->input_cmd2, p->cmd_path2);
	free_allocs(p->env_paths, NULL);
	free(p->infile);
	free(p->outfile);
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

//void	free_allocs(char ***alloc_array, char **alloc_str, char *print_str)
//{
//	size_t	i;
//
//	ft_printf("free from: %s\n", print_str);
//	i = 0;
//	if (alloc_array)
//		while (*alloc_array[i])
//			free(*alloc_array[i++]);
//	free(*alloc_array);
//	*alloc_array = NULL;
//	if (alloc_str)
//		free(*alloc_str);
//	*alloc_str = NULL;
//}

/* for debug */
/*
FILE	*fp = fopen("print", "w");
void	print_2d_arr(char **array, char *info_str, FILE *fp)
{
	size_t	i;

	i = 0;
	if (info_str)
		fprintf(fp, "#print_2d_arr");
	fprintf(fp, " %s:[", info_str);
	while (array[i])
		fprintf(fp, "%s,", array[i++]);
	fprintf(fp, "]\n");
}
*/
