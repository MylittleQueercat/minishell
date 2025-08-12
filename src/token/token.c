/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:25:12 by hguo              #+#    #+#             */
/*   Updated: 2025/08/12 16:51:45 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Convert a line of user input → into a token linked list -> return

t_token	*tokenizer(void)
{
	char	*line;
	t_token	*token_list;

	line = g_minishell.line;
	token_list = token_handler(line);
	free(line);
	g_minishell.line = NULL;
	return (token_list);
}
