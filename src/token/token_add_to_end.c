/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add_to_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:34:02 by hguo              #+#    #+#             */
/*   Updated: 2025/08/12 18:06:15 by hguo             ###   ########.fr       */
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

}	
