/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_globber.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 20:05:24 by hguo              #+#    #+#             */
/*   Updated: 2025/09/22 16:37:18 by aprigent         ###   ########.fr       */
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

static char	**globber_help(t_sh *sh, char *str)
{
	char			**result;
	struct dirent	*entry;
	DIR				*dir;
	size_t			count;

	count = match_count(str);
	if (!is_with_asterisk(str) || !count)
	{
		result = (char **)a_calloc(sh->a, 2, sizeof(char *));
		result[0] = a_strdup(sh->a, str);
		return (result);
	}
	else
	{
		dir = opendir(".");
		if (!dir)
			return (NULL);
		result = (char **)a_calloc(sh->a, count + 1, sizeof(char *));
		count = 0;
		while (set_direntry(&entry, dir) && entry)
			if (check_star(str, entry->d_name) && match_vis(str, entry->d_name))
				result[count++] = a_strdup(sh->a, entry->d_name);
		closedir(dir);
	}
	return (result);
}

char	**expand_globber(t_sh *sh, char **expanded)
{
	size_t	i;
	size_t	expanded_len;
	char	***globbed;

	expanded_len = get_str_arr_len(expanded);
	globbed = (char ***)a_calloc(sh->a, expanded_len + 1, sizeof(char **));
	i = 0;
	while (expanded[i])
	{
		globbed[i] = globber_help(sh, expanded[i]);
		i++;
	}
	return (join_str_arr(sh, globbed));
}
