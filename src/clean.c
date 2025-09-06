/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:41:29 by hguo              #+#    #+#             */
/*   Updated: 2025/09/05 16:04:00 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_envlst(t_minishell *sh)
{
	t_env	*envlst;
	t_env	*envlst_tofree;

	envlst = sh->envlst;
	while (envlst)
	{
		envlst_tofree = envlst;
		envlst = envlst->next;
		free(envlst_tofree->name);
		free(envlst_tofree->value);
		free(envlst_tofree);
	}
	sh->envlst = NULL;
}

void	clean_message(t_minishell *sh)
{
	go_trash(NULL, true);
	clear_ast(&sh->tree);
	clear_envlst(sh);
	rl_clear_history();
	tcsetattr(STDIN_FILENO, TCSANOW, &sh->original_term);
}
