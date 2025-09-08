/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:58:32 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/07 20:54:21 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* main loop of the shell
 * Reads user input, processes commands, and executes them.
 * This function will be expanded to handle command parsing etc.
 */

void	print_token_list(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		printf("Token: [%s] Type: [%d]\n", current->value, current->type);
		current = current->next;
	}
}

void	run_iteration(t_minishell *sh)
{
	init_signals(sh);
	build_prompt(sh);
	sh->line = readline(sh->prompt);
	if (!sh->line) // Ctrl-D
	{
		exit((printf("exit\n"), free_minishell(sh), 0));
		//eof_exit(sh);
	}
	if (sh->line[0])
		add_history(sh->line);
	sh->tokens = tokenizer(sh);
	if (!sh->tokens)
	{
		printf("Tokenization error\n");
		return (free(sh->line), (void)(sh->line = NULL));
	}
	sh->tree = parse(sh);
	if (sh->parse_err.type)
	{
		printf("Parsing error\n");
		handle_parse_err(sh);
		clear_ast(&sh->tree);
		clear_token_list(&sh->tokens);
		return (free(sh->line), (void)(sh->line = NULL),
				(void)(sh->parse_err.type = 0));
	}
	expander(sh);
	if (!sh->tree->exec_args && sh->tree->type == N_CMD)
	{
		printf("No command to execute after expansion\n");
		clear_ast(&sh->tree);
		clear_token_list(&sh->tokens);
		return (free(sh->line), (void)(sh->line = NULL));
	}
}
