/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:43:01 by hguo              #+#    #+#             */
/*   Updated: 2025/09/20 06:44:04 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_str_arr_len(char **str_arr)
{
	size_t	i;

	i = 0;
	while (str_arr[i])
		i++;
	return (i);
}

size_t	match_count(char *pattern)
{
	DIR				*dir;
	size_t			count;
	struct dirent	*entry;

	count = 0;
	dir = opendir(".");
	entry = readdir(dir);
	while (entry)
	{
		if (check_star(pattern, entry->d_name))
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

static size_t	count_str_arr(char	***str_arr)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	count = 0;
	while (str_arr[i])
	{
		j = 0;
		while (str_arr[i][j])
			j++;
		count += j;
		i++;
	}
	return (count);
}

char	**join_str_arr(t_sh *sh, char ***str_arr)
{
	size_t	i;
	size_t	j;
	size_t	count;
	char	**joined;

	count = count_str_arr(str_arr);
	joined = a_calloc(sh->a, count + 1, sizeof(char *));
	if (!joined)
		return (NULL);
	i = 0;
	count = 0;
	while (str_arr[i])
	{
		j = 0;
		while (str_arr[i][j])
		{
			joined[count + j] = a_strdup(sh->a, str_arr[i][j]);
			j++;
		}
		count += j;
		i++;
	}
	return (joined);
}
