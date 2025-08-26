/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:36:07 by hguo              #+#    #+#             */
/*   Updated: 2025/08/26 19:38:41 by hguo             ###   ########.fr       */
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

t_token	*token_handler(t_minishell *sh)
{
	int		invalid;
	t_token	*token_list;
	char	*p;

	invalid = 0;
	token_list = NULL;
	p = sh->line;
	while (*p)
	{
		if (invalid)
			return (clear_token_list(&token_list), NULL);
		if (ft_isspace(*p))
			skip_space(&p);
		else if (!ft_strncmp(p, "&&", 2) || !ft_strncmp(p, ">", 1)
			|| !ft_strncmp(p, "|", 1) || !ft_strncmp(p, "<", 1)
			|| !ft_strncmp(p, "(", 1) || !ft_strncmp(p, ")", 1))
			invalid = (!handler_sep(&p, &token_list) && 1);
		else
			invalid = (!add_word_to_end(sh, &p, &token_list) && 1);
	}
	return (token_list);
}

