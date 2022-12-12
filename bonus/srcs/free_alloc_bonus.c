/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_alloc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 22:12:15 by takira            #+#    #+#             */
/*   Updated: 2022/12/11 22:12:16 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex_bonu.h"

static void	free_alloc_array_b(char **alloc_array)
{
	size_t	i;

	i = 0;
	if (alloc_array)
		while (alloc_array[i])
			free(alloc_array[i++]);
	free(alloc_array);
}

void	free_and_ret_null_b(char **alloc_str)
{
	if (alloc_str)
		free(*alloc_str);
	*alloc_str = NULL;
}

void	free_allocs_b(t_pipe *p)
{
	free_alloc_array_b(p->env_paths);
	free_alloc_array_b(p->cmd1->cmds);
	free_alloc_array_b(p->cmd2->cmds);
	free_and_ret_null_b(&p->cmd1->path);
	free_and_ret_null_b(&p->cmd2->path);
	free(p->infile_name);
	free(p->outfile_name);
	free(p->cmd1);
	free(p->cmd2);
}

void	free_env_elem(void *content)
{
	t_env_elem	*elem;

	elem = content;
	free(elem->key);
	free(elem->val);
	free(content);
}
