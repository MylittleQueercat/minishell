/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:00:57 by hguo              #+#    #+#             */
/*   Updated: 2025/09/22 16:36:40 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	In this file, we replace input(ex: wildcards, quoters) with actual content,
	so that the command can be executed directly.
*/

static char	*cmd_pre_expand(t_sh *sh, char *str)
{
	char	*arr;
	size_t	i;

	arr = a_strdup(sh->a, "");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			arr = a_strjoin(sh->a, arr, handle_squotes(sh, str, &i));
		else if (str[i] == '"')
			arr = a_strjoin(sh->a, arr, handle_dquotes(sh, str, &i));
		else if (str[i] == '$')
			arr = a_strjoin(sh->a, arr, handle_dollar(sh, str, &i));
		else
			arr = a_strjoin(sh->a, arr, handle_normal(sh, str, &i));
	}
	return (arr);
}

/*
	1. Process quotes, variables, normal characters one by one
	2. Clear fragments that become empty after expansion
		(ex: $EMPTY expands to nothing)
	3. Split the entire str into an array of parameters
	4. Expand *.c into a list of matching files
	5. Remove quoters, so that finally the parameters passed to
		executor are only the string we actually wants
*/

static char	**pre_glob(t_sh *sh, char *str)
{
	char	**expanded;
	char	**globbed;

	if (!str)
		return (NULL);
	str = cmd_pre_expand(sh, str);
	if (!str)
		return (NULL);
	str = clean_empty(sh, str);
	if (!str)
		return (NULL);
	expanded = expand_split(sh, str);
	if (!expanded)
		return (NULL);
	globbed = expand_globber(sh, expanded);
	return (globbed);
}

void	expander(t_sh *sh, t_node *node)
{
	size_t	i;

	if (!node->raw_args)
		return (node->exec_args = NULL, (void)0);
	node->exec_args = pre_glob(sh, node->raw_args);
	if (!node->exec_args)
		exit((perror("malloc"), free_all(sh), 1));
	i = -1;
	while (node->exec_args[++i])
	{
		node->exec_args[i] = throw_quotes(sh, node->exec_args[i]);
		if (!node->exec_args[i])
			exit((perror("malloc"), free_all(sh), 1));
	}
}
