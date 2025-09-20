/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:58:32 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/20 08:02:21 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_iteration(t_sh *sh)
{
	init_signals(sh);
	build_prompt(sh);
	if (sh->prompt == NULL)
		exit((perror("Error malloc"), free_all(sh), 1));
	sh->line = readline(sh->prompt);
	if (!sh->line)
		exit((printf("exit\n"), free_all(sh), 0));
	if (sh->line && !*sh->line)
		return (g_st = 130, (void)0);
	if (sh->line[0])
		add_history(sh->line);
	sh->tokens = tokenizer(sh);
	if (!sh->tokens)
		return (g_st = 1, (void)0);
	sh->tree = parse(sh);
	if (sh->parse_err.type)
		return (g_st = 1, handle_parse_err(sh), (void)0);
	expander(sh, sh->tree);
	if (!sh->tree->exec_args && sh->tree->type == N_CMD)
		return (g_st = 1, printf("minishell: syntax error: "
				"empty command\n"), (void)0);
}
