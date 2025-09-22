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
		exit((perror("malloc"), free_all(sh), 1));
	sh->line = readline(sh->prompt);
	if (!sh->line)
		exit((ft_putstr_fd("exit\n", 2), free_all(sh), 0));
	if (sh->line && !*sh->line)
		return (g_st = 0, (void)0);
	if (sh->line[0])
		add_history(sh->line);
	sh->tokens = tokenizer(sh);
	if (!sh->tokens)
		return (g_st = 1, (void)0);
	sh->tree = parse(sh);
	if (sh->parse_err.type)
		return (g_st = 1, handle_parse_err(sh), (void)0);
}

void	loop(t_sh *sh)
{
	t_arena	*arena;

	while (1)
	{
		arena = malloc(sizeof(t_arena));
		if (!arena)
			exit((perror("malloc"), free_all(sh), 1));
		sh->a = arena;
		arena_init(arena, 1024 * 1024);
		if (arena->data == NULL)
			exit((perror("malloc"), free_all(sh), 1));
		run_iteration(sh);
		if (sh->line && !*sh->line)
		{
			free((free(sh->line), sh->line = NULL));
			arena_free(sh->a);
			continue ;
		}
		free((free(sh->line), sh->line = NULL));
		default_signals();
		if (sh->tree)
			run_exec(sh, sh->tree);
		arena_free(sh->a);
	}
}
