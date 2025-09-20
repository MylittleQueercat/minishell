/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:39:54 by hguo              #+#    #+#             */
/*   Updated: 2025/09/20 08:11:20 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node_type	get_node_type(t_token_type type)
{
	if (type == T_AND)
		return (N_AND);
	if (type == T_OR)
		return (N_OR);
	return (N_PIPE);
}

t_node	*create_new_node(t_sh *sh, t_node_type type)
{
	t_node	*new_node;

	new_node = (t_node *)a_calloc(sh->a, 1, sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	return (new_node);
}

t_io_type	get_io_type(t_token_type type)
{
	if (type == T_RD_IN)
		return (IO_IN);
	if (type == T_RD_OUT)
		return (IO_OUT);
	if (type == T_RD_HEREDOC)
		return (IO_HEREDOC);
	return (IO_ADD_END);
}

t_io_node	*create_new_io_node(t_sh *sh, t_token_type type, char *raw_v)
{
	t_io_node	*new_node;

	new_node = (t_io_node *)a_calloc(sh->a, 1, sizeof(t_io_node));
	if (!new_node)
		return (NULL);
	new_node->type = get_io_type(type);
	new_node->raw_value = a_strdup(sh->a, raw_v);
	if (!new_node->raw_value)
		return (NULL);
	return (new_node);
}

void	add_io_node_to_end(t_io_node **list, t_io_node *new)
{
	t_io_node	*current;

	if (!*list)
	{
		*list = new;
		return ;
	}
	current = *list;
	while (current && current->next)
		current = current->next;
	current->next = new;
}
