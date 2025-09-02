/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:06:14 by hguo              #+#    #+#             */
/*   Updated: 2025/09/02 17:02:56 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_char_arr2(char **arr)
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

	if (!lst || !*lst)
		return ;
	curr_node = *lst;
	while (curr_node)
	{
		next = curr_node->next;
		free(curr_node->raw_value);
		free_char_arr2(curr_node->exec_value);
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
	free(node->raw_args);
	free_char_arr2(node->exec_args);
}

void	clear_ast_node(t_node *node)
{
	if (!node)
		return ;
	clear_ast_node(node->left);
	clear_ast_node(node->right);
	if (node->type == N_CMD)
		clear_cmd_node(node);
	free(node);
}

void	clear_ast(t_node **ast)
{
	if (!ast || !*ast)
		return ;
	clear_ast_node(*ast);
	*ast = NULL;
}			
