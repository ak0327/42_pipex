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

#include "./../includes/pipex_bonu.h"

static t_env_elem	*get_env_key_val(char *env_i);

/* functions */
t_list	*get_env_lst(void)
{
	extern char	**environ;
	t_list		*envs;
	t_list		*new_node;
	t_env_elem	*env_elem;
	size_t		i;

	if (!environ)
		perror_and_exit_b("environ", EXIT_FAILURE);
	envs = NULL;
	i = 0;
	while (environ[i])
	{
		env_elem = get_env_key_val(environ[i]);
		new_node = ft_lstnew(env_elem);
		if (!env_elem || !new_node)
		{
			ft_lstclear(&envs, free_env_elem);
			perror_and_exit_b("malloc", EXIT_FAILURE);
		}
		ft_lstadd_back(&envs, new_node);
		i++;
	}
	return (envs);
}

char	*find_val_by_key(t_list *envs, char *search_key)
{
	t_env_elem		*env_elem;
	const size_t	key_len = ft_strlen_ns(search_key);

	if (!envs || !search_key)
		return ("");
	while (envs != NULL)
	{
		env_elem = envs->content;
		if (key_len == ft_strlen_ns(search_key)
			&& ft_strncmp_ns(env_elem->c_key, search_key, key_len) == 0)
			return (env_elem->c_val);
		envs = envs->next;
	}
	return ("");
}

static t_env_elem	*get_env_key_val(char *env_i)
{
	size_t			i;
	const size_t	len = ft_strlen_ns(env_i);
	t_env_elem		*env_elem;

	i = 0;
	while (env_i[i] && env_i[i] != '=')
		i++;
	if (i == 0 || i + 1 > len)
		return (NULL);
	env_elem = (t_env_elem *)malloc(sizeof(t_env_elem));
	if (!env_elem)
		return (NULL);
	env_elem->c_key = ft_substr(env_i, 0, i);
	env_elem->c_val = ft_substr(env_i, i + 1, len - (i + 1));
	if (!env_elem->c_key || !env_elem->c_val)
		return (NULL);
	return (env_elem);
}
