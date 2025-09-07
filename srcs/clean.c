/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:41:29 by hguo              #+#    #+#             */
/*   Updated: 2025/09/07 01:56:58 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_message(t_minishell *sh)
{
	go_trash(NULL, true);
	clear_ast(&sh->tree);
	rl_clear_history();
	tcsetattr(STDIN_FILENO, TCSANOW, &sh->original_term);
}
