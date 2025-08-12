/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:36:07 by hguo              #+#    #+#             */
/*   Updated: 2025/08/12 17:33:30 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  In this file, we'll split the entire command string entered by the user
into a token linked list:

  1. Iterate through the input string.
  2. Split the tokens according to the rules.
  3. Save to the linked list.
*/

int	handler_sep(char **line, t_token **token_list)
{
	if (!ft_strncmp(*line, "<<", 2))
		return (add_sep_to_end(T_RD_HEREDOC, line, token_list) && 1);
	else if (!ft_strncmp(*line, ">>", 2))
		return (add_sep_to_end(T_RD_ADD_END, line, token_list) && 1);
	else if (!ft_strncmp(*line, "<", 1))
		return (add_sep_to_end(T_RD_IN, line, token_list) && 1);
	else if (!ft_strncmp(*line, ">", 1))
		return (add_sep_to_end(T_RD_OUT, line, token_list) && 1);
	else if (!ft_strncmp(*line, "(", 1))
		return (add_sep_to_end(T_PAREN_OP, line, token_list) && 1);
	else if (!ft_strncmp(*line, ")", 1))
		return (add_sep_to_end(T_PAREN_CL, line, token_list) && 1);
	else if (!ft_strncmp(*line, "&&", 2))
		return (add_sep_to_end(T_AND, line, token_list) && 1);
	else if (!ft_strncmp(*line, "||", 2))
		return (add_sep_to_end(T_OR, line, token_list) && 1);
	else
		return (add_sep_to_end(T_PIPE, line, token_list) && 1);
}

t_token	*token_handler(char *line)
{
	int		invalid;
	t_token	*token_list;

	invalid = 0;
	token_list = NULL；
	while (*line)
	{
		if (invalid)
			return (token_list_clear(&token_list), NULL);
		if (ft_isspace(*line))
			ft_skip_space(&line);
		else if (!ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1)
			|| !ft_strncmp(line, "|", 1) || !ft_strncmp(line, "&&", 2)
			|| !ft_strncmp(line, "(", 1) || !ft_strncmp(line, ")", 1))
			invalid = (!handler_sep(&line, &token_list) && 1);
		else
			invalid = (add_word_to_end(&line, &token_list) && 1);
	}
	return (token_list);
}
