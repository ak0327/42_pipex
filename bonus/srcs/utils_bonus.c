/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:12:48 by takira            #+#    #+#             */
/*   Updated: 2022/12/09 21:48:29 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex_bonu.h"

/* functions */

void	ft_lstiter_fd(t_list *lst, int fd, void (*func)(char *, int))
{
	if (lst == NULL || func == NULL)
		return ;
	while (lst != NULL)
	{
		(*func)((char *)lst->content, fd);
		lst = lst->next;
	}
}

/* for debug */
//FILE	*fp = fopen("print", "w");

void	fprint_2d_arr_b(char **array, char *info_str, FILE *fp)
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

void	print_2d_arr_b(char **array, char *info_str)
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

void	debug_msg_str1_n_str2_nl_b(char *str1, int n, char *str2)
{
	ft_putstr_fd(str1, STDERR_FILENO);
	ft_putnbr_fd(n, STDERR_FILENO);
	ft_putstr_fd(str2, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	print_path(void *content)
{
	t_env_elem	*elem;

	elem = content;
	printf(" key:[%s]\n val:[%s]\n\n", elem->c_key, elem->c_val);
}
