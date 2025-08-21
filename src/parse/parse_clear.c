/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:06:14 by hguo              #+#    #+#             */
/*   Updated: 2025/08/21 16:41:11 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_arr2(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	clear_io_list(t_io_node **lst)
{
	t_io_node	*curr_node;
	t_io_node	*next;

	curr_node = *lst;
	if (!curr_node)
		return ;
	while (curr_node)
	{
		free(curr_node->value);
		free_str_arr2(curr_node->exec_value);
		next = curr_node->next;
		free(curr_node);
		curr_node = next;
	}
	*lst = NULL;
}

void	clear_cmd_node(t_node *node)
{
	if (!node)
		return ;
	clear_io_list(&(node->io_list));
	free(node->raw->args);
	free_str_arr2(node->exec_args);
}

void	clear_ast_node(t_node *node)
{
	if (!node)
		return ;
	if (node->type == N_CMD)
		clear_cmd_node(node);
	else
	{
		if (node->left)
			clear_ast_node(node->left);
		if (node->right)
			clear_ast_node(node->right);
	}
	free(node);
}

void	clear_ast(t_node **ast)
{
	clear_ast_node(*ast);
	*ast = NULL;
	clear_token_list(&g_minishell.token);
}			
