/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_signal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:31:01 by hguo              #+#    #+#             */
/*   Updated: 2025/09/07 01:59:16 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SIGNAL_H
# define MINI_SIGNAL_H

# include "minishell.h"
# include <stdbool.h>

typedef struct s_minishell	t_minishell;

typedef struct s_sigint_state
{
	bool		sigint_child;
	bool		sigint_heredoc;
}	t_sigint_state;

extern t_sigint_state		g_sigstate;

void					sig_handler(int num);
void					init_signals(t_minishell *sh);
void					sig_quit_handler(int num);

#endif
