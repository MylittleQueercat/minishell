/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:31:01 by hguo              #+#    #+#             */
/*   Updated: 2025/09/04 16:15:41 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include <stdbool.h>
# include <termios.h>
# include "minishell.h"

typedef struct s_minishell	t_minishell;

typedef struct s_signal_state
{
	bool	sigint_child;
	bool	heredoc_sigint;
}	t_sigint_state;

extern t_sigint_state	g_sigstate;

void	init_signals(t_minishell *sh);
void	sig_quit_handler(int num);

#endif
