/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:58:32 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/09 18:08:00 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_ast_token(t_minishell *sh)
{
	clear_ast(&sh->tree);
	clear_token_list(&sh->tokens);
	free(sh->line);
	sh->line = NULL;
}

void	run_iteration(t_minishell *sh)
{
	init_signals(sh);
	build_prompt(sh);
	sh->line = readline(sh->prompt);
	if (!sh->line)
		exit((printf("exit\n"), free_minishell(sh), 0));
	if (sh->line[0])
		add_history(sh->line);
	sh->tokens = tokenizer(sh);
	if (!sh->tokens)
		return (free(sh->line), printf("Token err\n"), (void)(sh->line = NULL));
	sh->tree = parse(sh);
	if (sh->parse_err.type)
	{
		printf("Parsing error\n");
		handle_parse_err(sh);
		clear_ast_token(sh);
		return ;
	}
	expander(sh, sh->tree);
	if (!sh->tree->exec_args && sh->tree->type == N_CMD)
	{
		printf("No command to execute after expansion\n");
		clear_ast_token(sh);
		return ;
	}
}
