/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lsts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:46:49 by takira            #+#    #+#             */
/*   Updated: 2022/12/11 16:46:51 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex_bonus.h"

static t_env_elem	*get_env_key_val(char *env_i);

/* functions */
t_list	*get_env_lst(t_pipe *p, int exit_fail_no)
{
	t_list		*envs;
	t_list		*new_node_m;
	t_env_elem	*env_elem_m;
	size_t		i;

	if (!p->c_environ)
		exit_with_perror_free_b("environ", exit_fail_no, p);
	envs = NULL;
	i = 0;
	while (p->c_environ[i])
	{
		env_elem_m = get_env_key_val(p->c_environ[i]);
		new_node_m = ft_lstnew(env_elem_m);
		if (!env_elem_m || !new_node_m)
		{
			ft_lstclear(&envs, free_env_elems);
			exit_with_perror_free_b("malloc", exit_fail_no, p);
		}
		ft_lstadd_back(&envs, new_node_m);
		i++;
	}
	return (envs);
}

char	*search_val_in_envs(t_list *envs, char *search_key)
{
	t_env_elem		*env_elem;
	const size_t	key_len = ft_strlen_ns(search_key);

	if (!envs || !search_key)
		return ("");
	while (envs != NULL)
	{
		env_elem = envs->content;
		if (key_len == ft_strlen_ns(search_key)
			&& ft_strncmp_ns(env_elem->c_key_m, search_key, key_len) == 0)
			return (env_elem->c_val_m);
		envs = envs->next;
	}
	return ("");
}

static t_env_elem	*get_env_key_val(char *env_i)
{
	size_t			i;
	const size_t	len = ft_strlen_ns(env_i);
	t_env_elem		*env_elem_m;

	i = 0;
	while (env_i[i] && env_i[i] != '=')
		i++;
	if (i == 0 || i + 1 > len)
		return (NULL);
	env_elem_m = (t_env_elem *)malloc(sizeof(t_env_elem));
	if (!env_elem_m)
		return (NULL);
	env_elem_m->c_key_m = ft_substr(env_i, 0, i);
	env_elem_m->c_val_m = ft_substr(env_i, i + 1, len - (i + 1));
	if (!env_elem_m->c_key_m || !env_elem_m->c_val_m)
		return (NULL);
	return (env_elem_m);
}
