/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:20:27 by hguo              #+#    #+#             */
/*   Updated: 2025/09/20 06:45:11 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_word(char const *s, size_t *i)
{
	char	quotes;

	while (s[*i] && s[*i] != ' ')
	{
		if (s[*i] != '\'' && s[*i] != '"')
			(*i)++;
		else
		{
			quotes = s[(*i)++];
			while (s[(*i)] != quotes)
				(*i)++;
			(*i)++;
		}
	}
}

static char	**allocate_mem(t_minishell *sh, char const *str, char **res)
{
	size_t	begin;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			begin = i;
			skip_word(str, &i);
			res[j] = a_calloc(sh->a, i - begin + 1, sizeof(char));
			if (!res[j])
				return (NULL);
			j++;
		}
		while (str[i] && str[i] == ' ')
			i++;
	}
	return (res);
}

static void	fill_word(char const *str, char **res, size_t *i, size_t j)
{
	char	quotes;
	size_t	k;

	k = 0;
	while (str[(*i)] && str[(*i)] != ' ')
	{
		if (str[(*i)] != '\'' && str[(*i)] != '"')
			res[j][k++] = str[(*i)++];
		else
		{
			quotes = str[(*i)++];
			res[j][k++] = quotes;
			while (str[(*i)] != quotes)
				res[j][k++] = str[(*i)++];
			res[j][k++] = str[(*i)++];
		}
	}
}

static char	**filler(char const *str, char **res)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] && res[j])
	{
		if (str[i] != ' ')
		{
			fill_word(str, res, &i, j);
			j++;
		}
		while (str[i] && str[i] == ' ')
			i++;
	}
	return (res);
}

char	**expand_split(t_minishell *sh, char const *str)
{
	size_t	i;
	size_t	count;
	char	**res;
	char	**to_free;

	if (!str)
		return (NULL);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != ' ' && ++count)
			skip_word(str, &i);
		while (str[i] && str[i] == ' ')
			i++;
	}
	res = a_calloc(sh->a, count + 1, sizeof(char *));
	to_free = res;
	res = allocate_mem(str, res);
	if (!res || !count)
		return (NULL);
	return (filler(str, res));
}
