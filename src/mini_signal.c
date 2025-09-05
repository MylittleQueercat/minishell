/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:52:55 by hguo              #+#    #+#             */
/*   Updated: 2025/09/05 16:06:59 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sigint_state	g_sigstate = {false, false};

void	sig_handler(int num)
{
	(void)num;
	if (g_sigstate.sigint_child)
	{
		ft_putstr_fd("\n", 1);
		g_sigstate.sigint_child = false;
		g_sigstate.heredoc_sigint = true;
	}
	else
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_quit_handler(int num)
{
	(void)num;
	ft_putstr_fd("Quit: 3\n", 1);
}

void	init_signals(t_minishell *sh)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &sh->original_term);
	term = sh->original_term;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	g_sigstate.heredoc_sigint = false;
	g_sigstate.sigint_child = false;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
