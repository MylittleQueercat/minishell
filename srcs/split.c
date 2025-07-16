/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:03:51 by aprigent          #+#    #+#             */
/*   Updated: 2025/07/12 18:04:26 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(const char *str)
{
	int	count;
	int	i;
	int	in_quotes;

	count = 0;
	i = 0;
	in_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			in_quotes = !in_quotes;
		if (!in_quotes && str[i] == ' ')
		{
			while (str[i] && str[i] == ' ')
				i++;
			if (str[i])
				count++;
		}
		else
			i++;
	}
	if (i > 0 && str[i - 1] != ' ')
		count++;
	return (count);
}

char	**condition(const char *str, char **result, t_split *value)
{
	while (str[value->i] && str[value->i] == ' ')
		value->i++;
	if (str[value->i] == '\'')
		value->in_quotes = !value->in_quotes;
	if (!value->in_quotes && str[value->i] == ' ')
	{
		while (str[value->i] && str[value->i] == ' ')
			value->i++;
	}
	else
	{
		value->k = value->i;
		while (str[value->i] && (str[value->i] != ' ' || value->in_quotes))
		{
			if (str[++value->i] == '\'')
				value->in_quotes = !value->in_quotes;
		}
		result[value->j++] = ft_substr(str, value->k, value->i - value->k);
		if (!result[value->j - 1])
			return (free_array(result), NULL);
	}
	return (result);
}

char	**split_input(const char *str)
{
	char	**result;
	t_split	value;

	ft_bzero(&value, sizeof(t_split));
	result = malloc(sizeof(char *) * (count_words(str) + 1));
	if (!result)
		return (NULL);
	while (str[value.i])
	{
		result = condition(str, result, &value);
		if (!result)
			return (NULL);
	}
	result[value.j] = NULL;
	return (result);
}
