/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:06:09 by hguo              #+#    #+#             */
/*   Updated: 2025/08/27 20:43:19 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_bi_operator(t_token *tok)
{
	if (!tok)
		return (0);
	return (tok->type == T_PIPE || tok->type == T_AND || tok->type == T_OR);
}

int	get_priority(t_token_type type)
{
	if (type == T_OR || type == T_AND)
		return (0);
	return (1);
}

int	curr_priority(t_token *tok)
{
	if (tok)
		return (get_priority(tok->type));
	else
		return (-1);
}

int	is_redir(t_token_type type)
{
	if (type == T_RD_IN || type == T_RD_OUT || type == T_RD_HEREDOC
		|| type == T_RD_ADD_END)
		return (1);
	return (0);
}
