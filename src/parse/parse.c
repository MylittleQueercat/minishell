/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:42:05 by hguo              #+#    #+#             */
/*   Updated: 2025/08/13 18:39:37 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* In this file, we convert the token string into a command syntax tree. */

/* Parse the smallest units (use recursion) */
t_node	*parse_cmd_unit(void)
{
	t_node	*node;

	if (g_minishell.parse_err.type)
		return (NULL);
	if (is_bi_operator() || g_minishell.current->type == T_PAREN_CL)
		return (set_parse_err(E_SYNTAX), NULL);
	else if (g_minishell.current->type == T_PAREN_OP)
	{
		get_next_token();
		node = parse_cmd(0);
		if (!node)
			return (set_parse_err(E_MEMORY), NULL);
		if (!g_minishell.curent || g_minishell.current->type != T_PAREN_CL)
			return (set_parse_err(E_STNTAX), node);
		get_next_token();
		return (node);
	}
	else
		return (...
}

/* 
   Link the left and right subtrees, so the executor can run the commands in 
   logical order.
*/
t_node	*combine_cmd(t_token_type operator, t_node *left, t_node *right)
{
	t_node	*node;

	if (g_minishell.parse_err.type)
		return (NULL);
	node = create_new_node(get_node_type(operator));
	if (!node)
		return (set_parse_err(E_MEMORY), NULL);
	node->left = left;
	node->right = right;
	return (node);
}

/* Combine units into larger structures according to operator priority */
t_node	*parse_cmd(int min_prio)
{
	t_node			*left;
	t_node			*right;
	int				next_prio;
	t_token_type	operator;

	if (g_minishell.parse_err.type || !g_minishell.current)
		return (NULL);
	left = parse_cmd_unit();
	if (!left)
		return (NULL);
}

t_node	*parse(void)
{
	t_node	*cmd_tree;

	g_minishell.current = g_minishell.tokens;
	cmd_tree = parse_cmd(0);
	if (g_minishell.current)
		return (set_parse_err(E_SYNTAX), cmd_tree);
	return (cmd_tree);
}
