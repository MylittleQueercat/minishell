/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:42:05 by hguo              #+#    #+#             */
/*   Updated: 2025/09/04 17:48:46 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* In this file, we convert the token string into a command syntax tree. */

/* Parse the smallest units (use recursion) */
t_node	*parse_cmd_unit(t_minishell *sh, t_token **it)
{
	t_node	*node;

	if (sh->parse_err.type)
		return (NULL);
	if (*it && (is_bi_operator(*it) || (*it && (*it)->type == T_PAREN_CL)))
		return (set_parse_err(sh, E_SYNTAX), NULL);
	else if (*it && (*it)->type == T_PAREN_OP)
	{
		*it = (*it)->next;
		node = parse_cmd(sh, it, 0);
		if (!node)
			return (set_parse_err(sh, E_MEMORY), NULL);
		if (!*it || (*it)->type != T_PAREN_CL)
			return (set_parse_err(sh, E_SYNTAX), node);
		*it = (*it)->next;
		return (node);
	}
	else
		return (read_simple_cmd(sh, it));
}

/*
   Link the left and right subtrees, so the executor can run the commands in
   logical order.
*/
t_node	*comb_cmd(t_minishell *sh, t_token_type op, t_node *lf, t_node *rg)
{
	t_node	*node;

	if (sh->parse_err.type)
		return (NULL);
	node = create_new_node(get_node_type(op));
	if (!node)
	{
		set_parse_err(sh, E_MEMORY);
		return (NULL);
	}
	node->left = lf;
	node->right = rg;
	return (node);
}

/* Combine units into larger structures according to operator priority */
t_node	*parse_cmd(t_minishell *sh, t_token **it, int min_prio)
{
	t_node			*left;
	t_node			*right;
	int				next_prio;
	t_token_type	op;

	if (sh->parse_err.type || !*it)
		return (NULL);
	left = parse_cmd_unit(sh, it);
	if (!left)
		return (NULL);
	while (*it && is_bi_operator(*it) && curr_priority(*it) >= min_prio)
	{
		op = (*it)->type;
		*it = (*it)->next;
		if (!*it)
			return (set_parse_err(sh, E_SYNTAX), left);
		next_prio = get_priority(op) + 1;
		right = parse_cmd(sh, it, next_prio);
		if (!right)
			return (left);
		left = comb_cmd(sh, op, left, right);
		if (!left)
			return (clear_ast(&left), clear_ast(&right), NULL);
	}
	return (left);
}

t_node	*parse(t_minishell *sh)
{
	t_node	*cmd_tree;
	t_token	*it;

	it = sh->tokens;
	if (!it)
		return (NULL);
	sh->parse_err.type = 0;
	sh->parse_err.msg = NULL;
	cmd_tree = parse_cmd(sh, &it, 0);
	if (it && !sh->parse_err.type)
		return (set_parse_err(sh, E_SYNTAX), cmd_tree);
	return (cmd_tree);
}
