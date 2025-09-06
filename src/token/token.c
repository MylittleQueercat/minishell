/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:25:12 by hguo              #+#    #+#             */
/*   Updated: 2025/08/26 19:04:54 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Convert a line of user input → into a token linked list -> return

t_token	*tokenizer(t_minishell *sh)
{
	t_token	*token_list;

	if (!sh->line)
		return (NULL);
	token_list = token_handler(sh);
	free(sh->line);
	sh->line = NULL;
	return (token_list);
}
