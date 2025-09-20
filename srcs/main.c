/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:51:28 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/20 07:52:39 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_st = 0;

int	main(int argc, char **argv, char **envp)
{
	t_sh	*sh;
	t_arena		*arena;

	if (argc != 1)
		return (printf("Usage : %s\n", argv[0]), 1);
	sh = setup_minishell(envp);
	if (!sh)
		return (perror("Error malloc\n"), 1);
	while (1)
	{
		arena = malloc(sizeof(t_arena));
		if (!arena)
			return (free_all(sh), 1);
		sh->a = arena;
		arena_init(arena, 1024 * 1024);
		if (arena->data == NULL)
			return (perror("malloc"), free_all(sh), 1);
		run_iteration(sh);
		if (sh->tree)
			run_exec(sh, sh->tree);
		arena_free(sh->a);
	}
	return (free_all(sh), g_st);
}
