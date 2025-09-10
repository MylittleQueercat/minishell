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

void	print_ast(t_node *node)
{
	if (!node)
		return ;
	printf("Node type: %d\n", node->type);
	if (node->type == N_CMD)
	{
		if (node->raw_args)
			printf("  Raw args: %s\n", node->raw_args);
		if (node->exec_args)
		{
			printf("  Exec args: ");
			for (int i = 0; node->exec_args[i]; i++)
				printf("'%s' ", node->exec_args[i]);
			printf("\n");
		}
	}
	if (node->left)
	{
		printf("Left:\n");
		print_ast(node->left);
	}
	if (node->right)
	{
		printf("Right:\n");
		print_ast(node->right);
	}
}

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
	print_ast(sh->tree);
}
