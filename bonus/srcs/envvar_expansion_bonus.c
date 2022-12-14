/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  envvar_ expansion_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:41:10 by takira            #+#    #+#             */
/*   Updated: 2022/12/11 16:41:11 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex_bonus.h"

/* prototype declaration */
static char		*expand_var(char *line, size_t kwod_len, char *val, size_t i);
static char		*search_key(char *line, size_t i, size_t len, t_list *envs);
static size_t	get_key_len(const char *line, size_t i);
static int		is_var_candidate(const char *line, size_t i);

/* functions */
char	*expand_env_var_controller(char *line, t_list *envs)
{
	size_t	i;
	size_t	key_wo_dollar_len;
	char	*env_key;
	char	*env_val;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && is_var_candidate(line, i) == true)
		{
			key_wo_dollar_len = get_key_len(line, i + 1);
			env_key = search_key(line, i + 1, key_wo_dollar_len, envs);
			env_val = search_val_in_envs(envs, env_key);
			line = expand_var(line, key_wo_dollar_len, env_val, i);
			if (!line)
				return (NULL);
			i += ft_strlen_ns(env_val);
			continue ;
		}
		i++;
	}
	return (line);
}

static char	*expand_var(char *line, size_t kwod_len, char *val, size_t i)
{
	const size_t	val_len = ft_strlen_ns(val);
	char			*new_line;
	size_t			new_line_len;

	new_line_len = ft_strlen_ns(line) - (kwod_len + 1) + val_len;
	new_line = (char *)ft_calloc(sizeof(char), new_line_len + 1);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	ft_strlcat(new_line, line, i + 1);
	ft_strlcat(new_line, val, new_line_len + 1);
	ft_strlcat(new_line, &line[i + kwod_len + 1], new_line_len + 1);
	free(line);
	return (new_line);
}

static int	is_var_candidate(const char *line, size_t i)
{
	if (line[i] == '$' && \
	((i > 0 && line[i - 1] == '\\') \
	|| line[i + 1] == '$' \
	|| line[i + 1] == ' ' \
	|| line[i + 1] == '\0' \
	|| line[i + 1] == '\n'))
		return (false);
	return (true);
}

static size_t	get_key_len(const char *line, size_t i)
{
	size_t	len;

	len = 0;
	while (line[i + len] \
	&& line[i + len] != '\n' \
	&& line[i + len] != ' ' \
	&& line[i + len] != '"' \
	&& line[i + len] != '$')
		len++;
	return (len);
}

static char	*search_key(char *line, size_t i, size_t len, t_list *envs)
{
	t_env_elem	*env_elem;

	if (envs == NULL)
		return (NULL);
	while (envs != NULL)
	{
		env_elem = envs->content;
		if (ft_strlen_ns(env_elem->c_key_m) == len
			&& ft_strncmp_ns(env_elem->c_key_m, &line[i], len) == 0)
			return (env_elem->c_key_m);
		envs = envs->next;
	}
	return (NULL);
}
