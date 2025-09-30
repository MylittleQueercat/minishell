/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:58:32 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/22 16:54:51 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_sh_struct(t_sh *sh)
{
	sh->tokens = NULL;
	sh->tree = NULL;
	sh->parse_err.type = 0;
	sh->prompt = NULL;
}

void	run_iteration(t_sh *sh)
{
	char	*tmp;

	init_signals(sh);
	build_prompt(sh);
	if (sh->prompt == NULL)
		exit((perror("malloc"), free_all(sh), 1));
	tmp = readline(sh->prompt);
	sh->line = a_strdup(sh->a, tmp);
	if (tmp)
		free(tmp);
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
		return (g_st = 2, handle_parse_err(sh), (void)0);
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
			arena_free(sh->a);
			continue ;
		}
		if (sh->tree)
			run_exec(sh, sh->tree);
		arena_free(sh->a);
		reset_sh_struct(sh);
	}
}
