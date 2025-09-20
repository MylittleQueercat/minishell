/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_signal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:31:01 by hguo              #+#    #+#             */
/*   Updated: 2025/09/20 08:03:28 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SIGNAL_H
# define MINI_SIGNAL_H

# include "minishell.h"
# include <stdbool.h>

typedef struct s_sh	t_sh;

typedef struct s_sigint_state
{
	bool		sigint_child;
	bool		sigint_heredoc;
}	t_sigint_state;

extern t_sigint_state		g_sigstate;

void					sig_handler(int num);
void					init_signals(t_sh *sh);
void					sig_quit_handler(int num);

#endif
