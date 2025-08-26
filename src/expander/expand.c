/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:00:57 by hguo              #+#    #+#             */
/*   Updated: 2025/08/21 20:21:20 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	In this file, we replace input(ex: wildcards, quoters) with actual content,
	so that the command can be executed directly.
*/

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = ft_calloc(len, sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	while (s1[i])
		joined[i++] = s1[i++];
	j = 0;
	while (s2[j])
		joined[i++] = s2[j++];
	joined[i] = 0;
	return (free(s1), free(s2), joined);
}

static char	*cmd_pre_expand(char *str)
{
	char	*arr;
	size_t	i;

	arr = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			arr = ft_strjoin_free(arr, handle_squotes(str, &i));
		else if (str[i] == '"')
			arr = ft_strjoin_free(arr, handle_dquotes(str, &i));
		else if (str[i] == '$')
			arr = ft_strjoin_free(arr, handle_dollar(str, &i));
		else
			arr = ft_strjoin_free(arr, handle_normal(str, &i));
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

char	**expander(char *str)
{
	char	**expanded;
	char	**globbed;
	size_t	i;

	str = cmd_pre_expand(str);
	if (!str)
		return (NULL);
	str = clean_empty(str);
	if (!str)
		return (NULL);
	expanded = expand_split(str);
	free(str);
	if (!expanded)
		return (NULL);
	globbed = expand_globber(expanded);
	if (!globbed)
		return (NULL);
	i = 0;
	while(globbed[i])
	{
		globbed[i] = throw_quotes(globbed[i]);
		i++;
	}
	return (globbed);
}
