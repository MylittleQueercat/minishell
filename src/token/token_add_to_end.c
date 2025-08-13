/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add_to_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:34:02 by hguo              #+#    #+#             */
/*   Updated: 2025/08/13 16:04:58 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*  In this file, we create tokens (separators or words), and add them to the 
*  end of the token list in order, while moving the input pointer to the next 
*  unprocessed position.
*/

int	add_sep_to_end(t_token_type type, char **line, t_token **token_list)
{
	t_token	*token;

	token = create_new_token(NULL, type);
	if (!token)
		return (0);
	token_list_add_back(token_list, token);
	(*line)++;
	if (type == T_RD_HEREDOC || type == T_RD_ADD_END || type == T_AND
		|| type == T_OR)
		(*line)++;
	return (1);	
}

int	add_word_to_end(char **line, t_token **token_list)
{
	char	*curr_place;
	char	*value;
	t_token	*token;
	size_t	i;

	curr_place = *line;
	i = 0;
	while (curr_place[i] && !is_sep(curr_place + i))
	{
		if (is_quote(curr_place[i]))
		{
			if (!skip_quote(curr_place, &i))
				return (print_quote_err(curr_place[i]), 0);
		}
		else
			i++;
	}
	value = ft_substr(curr_place, 0, i);
	if (!value)
		return (0);
	token = create_new_token(value, T_WORD);
	if (!token)
		return (free(value), 0);
	*line += 1;
	return (token_list_add_back(token_list, token), 1);
}	
