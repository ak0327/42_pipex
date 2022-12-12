/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:10:04 by takira            #+#    #+#             */
/*   Updated: 2022/12/09 21:47:52 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/pipex_bonu.h"

static char	**free_array_b(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	return (NULL);
}

static void	get_strs_size_b(const char *str, char delim, char set, size_t *cnt)
{
	size_t	set_cnt;
	size_t	i;

	set_cnt = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == delim)
			i++;
		if (str[i] && str[i] != set)
		{
			if (set_cnt % 2 == 0)
				*cnt += 1;
			while (str[i] && str[i] != delim && str[i] != set)
				i++;
		}
		if (str[i] && str[i] == set)
		{
			set_cnt++;
			if (set_cnt % 2 == 1)
				*cnt += 1;
			i++;
		}
	}
}

static size_t	get_split_idx_b(const char *s, char d, char set, size_t *head)
{
	size_t	tail;
	bool	is_in_set;

	while (s[*head] && s[*head] == d)
		*head += 1;
	is_in_set = false;
	if (s[*head] == set)
		is_in_set = true;
	tail = *head;
	if (is_in_set)
		tail++;
	if (is_in_set)
		while (s[tail] && s[tail] != set)
			tail++;
	else
		while (s[tail] && s[tail] != d && s[tail] != set)
			tail++;
	return (tail);
}

static char	**get_split_strs_b(char **strs, const char *s, char d, char set)
{
	size_t	i;
	size_t	head_idx;
	size_t	tail_idx;
	size_t	head_shift;

	i = 0;
	head_idx = 0;
	while (s[head_idx])
	{
		head_shift = 0;
		tail_idx = get_split_idx_b(s, d, set, &head_idx);
		if (head_idx >= tail_idx || (s[head_idx] == d && !s[tail_idx]))
			break ;
		if (s[head_idx] == set)
			head_shift = 1;
		head_idx += head_shift;
		strs[i] = ft_substr(s, head_idx, tail_idx - head_idx);
		if (!strs[i])
			return (free_array_b(strs));
		i++;
		head_idx = tail_idx;
		if (s[tail_idx])
			head_idx += head_shift;
	}
	return (strs);
}

char	**ft_split_set_b(const char *str, char delim, char set)
{
	char	**strs;
	size_t	strs_size;

	if (!str || delim == set)
		return (NULL);
	strs_size = 0;
	if (delim)
		get_strs_size_b(str, delim, set, &strs_size);
	strs = (char **)ft_calloc(sizeof(char *), strs_size + 1);
	if (!strs)
		return (NULL);
	get_split_strs_b(strs, str, delim, set);
	if (!strs)
		return (NULL);
	strs[strs_size] = NULL;
	return (strs);
}
