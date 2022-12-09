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
static void	free_alloc_array(char **alloc_array)
{
	size_t	i;

	i = 0;
	if (alloc_array)
		while (alloc_array[i])
			free(alloc_array[i++]);
	free(alloc_array);
}

void	free_and_ret_null(char **alloc_str)
{
	if (alloc_str)
		free(*alloc_str);
	*alloc_str = NULL;
}

void	free_allocs(t_pipe *p)
{
	free_alloc_array(p->env_paths);
	free_alloc_array(p->cmd1->cmds);
	free_alloc_array(p->cmd2->cmds);
	free_and_ret_null(&p->cmd1->path);
	free_and_ret_null(&p->cmd2->path);
	free(p->infile_name);
	free(p->outfile_name);
	free(p->cmd1);
	free(p->cmd2);
}

/* for debug */
//FILE	*fp = fopen("print", "w");
/*
void	fprint_2d_arr(char **array, char *info_str, FILE *fp)
{
	size_t	i;

	i = 0;
	if (info_str)
		fprintf(fp, "#print_2d_arr");
	fprintf(fp, " %s:[", info_str);
	while (array[i])
	{
		if (i != 0)
			printf(",");
		fprintf(fp, "'%s'", array[i++]);
	}
	fprintf(fp, "]\n");
}

void	print_2d_arr(char **array, char *info_str)
{
	size_t	i;

	i = 0;
	if (info_str)
		printf("#print_2d_arr");
	printf(" %s:[", info_str);
	while (array[i])
	{
		if (i != 0)
			printf(",");
		printf("'%s'", array[i++]);
	}
	printf("]\n");
}

void	debug_msg_str1_n_str2_nl(char *str1, int n, char *str2)
{
	ft_putstr_fd(str1, STDERR_FILENO);
	ft_putnbr_fd(n, STDERR_FILENO);
	ft_putstr_fd(str2, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
*/