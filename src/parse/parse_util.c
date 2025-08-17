/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:06:09 by hguo              #+#    #+#             */
/*   Updated: 2025/08/17 13:21:01 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_to_next_token(void)
{
	g_minishell.current = g_minishell.current->next;
}

int	is_bi_operator(void)
{
	t_token_type	type;

	if (!g_minishell.current)
		return (0);
	type = g_minishell.current->type;
	if (type == T_PIPE || type == T_AND || type == T_OR)
		return (1);
	return (0);
}

int	get_priority(t_token_type type)
{
	if (type == T_OR || type == T_AND)
		return (0);
	return (1);
}

int	curr_priority(void)
{
	return (get_priority(g_minishell.current->type));
}

int	is_redir(t_token_type type)
{
	if (type == T_RD_IN || type == T_RD_OUT || type == T_RD_HEREDOC
		|| type == T_RD_ADD_END)
		return (1);
	return (0);
}
