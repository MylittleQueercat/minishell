/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:41:29 by hguo              #+#    #+#             */
/*   Updated: 2025/09/20 08:05:20 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_message(t_sh *sh)
{
	rl_clear_history();
	tcsetattr(STDIN_FILENO, TCSANOW, &sh->original_term);
}
