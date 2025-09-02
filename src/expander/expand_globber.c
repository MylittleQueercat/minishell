/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_globber.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 20:05:24 by hguo              #+#    #+#             */
/*   Updated: 2025/09/02 17:31:12 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_with_asterisk(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

int	match_vis(char *pattern, char *str)
{
	if ((pattern[0] == '.' && str[0] == '.') 
		|| (pattern[0] != '.' && str[0] != '.'))
		return (1);
	return (0);
}

int	set_direntry(struct dirent **entry, DIR *dir)
{
	*entry = readdir(dir);
	return (1);
}

static char	**globber_help(char *str)
{
	char			**result;
	struct dirent	*entry;
	DIR				*dir;
	size_t			count;

	count = match_count(str);
	if (!is_with_asterisk(str) || !count)
	{
		result = (char **)ft_calloc(2, sizeof(char *));
		result[0] = ft_strdup(str);
		return (result);
	}
	else
	{
		dir = opendir(".");
		result = (char **)ft_calloc(count + 1, sizeof(char *));
		count = 0;
		while (set_direntry(&entry, dir) && entry)
			if (check_star(str, entry->d_name) && match_vis(str, entry->d_name))
				result[count++] = ft_strdup(entry->d_name);
		closedir(dir);
	}
	return (result);
}

char	**expand_globber(char **expanded)
{
	size_t	i;
	size_t	expanded_len;
	char	***globbed;

	expanded_len = get_str_arr_len(expanded);
	globbed = (char ***)ft_calloc(expanded_len + 1, sizeof(char **));
	i = 0;
	while (expanded[i])
	{
		globbed[i] = globber_help(expanded[i]);
		i++;
	}
	return (free_char_arr2(expanded), join_str_arr(globbed));
}
