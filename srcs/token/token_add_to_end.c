/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add_to_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:34:02 by hguo              #+#    #+#             */
/*   Updated: 2025/09/28 18:43:24 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*  In this file, we create tokens (separators or words), and add them to the
*  end of the token list in order, while moving the input pointer to the next
*  unprocessed position.
*/

int	add_sep_to_end(t_sh *m, t_token_type type, char **line, t_token **t_l)
{
	t_token	*token;

	token = create_new_token(m, NULL, type);
	if (!token)
		return (0);
	token_list_add_back(t_l, token);
	(*line)++;
	if (type == T_RD_HEREDOC || type == T_RD_ADD_END || type == T_AND
		|| type == T_OR)
		(*line)++;
	return (1);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	add_word_to_end(t_sh *sh, char **line, t_token **token_list)
{
	char	*curr_place;
	char	*value;
	t_token	*token;
	size_t	i;
	int		quoted;

	curr_place = *line;
	i = 0;
	quoted = 0;
	while (curr_place[i] && !is_sep(curr_place + i))
	{
		if (is_quote(curr_place[i]))
		{
			quoted = 1;
			if (!skip_quote(*line, &i))
				return (print_quote_err(sh, curr_place[i]), 0);
		}
		else
			i++;
	}
	value = a_substr(sh->a, curr_place, 0, i);
	if (!value)
		return (0);
	token = create_new_token(sh, value, T_WORD);
	if (!token)
		return (0);
	token->quoted = quoted;
	*line += i;
	return (token_list_add_back(token_list, token), 1);
}
