/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:59:28 by hguo              #+#    #+#             */
/*   Updated: 2025/09/20 08:05:42 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_new_token(t_sh *sh, char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)a_calloc(sh->a, 1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
	return (new_token);
}

void	token_list_add_back(t_token **list, t_token *new_token)
{
	t_token	*current;

	if (!*list)
	{
		*list = new_token;
		return ;
	}
	current = *list;
	while (current && current->next)
		current = current->next;
	current->next = new_token;
	new_token->before = current;
}
