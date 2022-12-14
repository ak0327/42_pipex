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

#include "./../includes/pipex_bonus.h"

/* prototype declaration */
static void	free_cmds(void *content);
static void	free_2d_array_b(char ***alloc_array);
//void	free_lst(void *content);

/* functions */
void	free_allocs_b(t_pipe *p)
{
	if (p)
	{
		free_2d_array_b(&p->c_paths_m);
		ft_lstclear(&p->t_cmd_list_m, free_cmds);
		free(p->t_cmd_list_m);
		p->t_cmd_list_m = NULL;
		ft_lstclear(&p->t_here_doc_contents, free);
		free_1d_array_b(&p->c_infile_name_m);
		free_1d_array_b(&p->c_outfile_name_m);
	}
}

void	free_env_elems(void *content)
{
	t_env_elem	*elem;

	elem = content;
	free_1d_array_b(&elem->c_key_m);
	free_1d_array_b(&elem->c_val_m);
	free(content);
}

static void	free_2d_array_b(char ***alloc_array)
{
	size_t	i;

	i = 0;
	if (alloc_array && *alloc_array)
		while ((*alloc_array)[i])
			free((*alloc_array)[i++]);
	free(*alloc_array);
	*alloc_array = NULL;
}

void	free_1d_array_b(char **alloc_str)
{
	if (alloc_str)
		free(*alloc_str);
	*alloc_str = NULL;
}

static void	free_cmds(void *content)
{
	t_cmd	*cmd;

	cmd = content;
	free_2d_array_b(&cmd->c_cmds_m);
	free_1d_array_b(&cmd->c_path_m);
	free(content);
}
