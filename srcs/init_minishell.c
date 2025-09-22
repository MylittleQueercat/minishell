/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 18:09:12 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/20 07:49:48 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sh	*setup_minishell(char **envp)
{
	t_sh	*sh;
	t_arena		*sh_arena;

	sh_arena = malloc(sizeof(t_arena));
	if (!sh_arena)
		return (NULL);
	arena_init(sh_arena, 1024 * 1024);
	if (!sh_arena->data)
		return (free(sh_arena), NULL);
	sh = arena_alloc(sh_arena, sizeof(t_sh));
	if (!sh)
		return (arena_free(sh_arena), NULL);
	ft_bzero(sh, sizeof(*sh));
	sh->sh_arena = sh_arena;
	init_sh(sh, envp);
	return (sh);
}

void	init_sh(t_sh *sh, char **env)
{
	sh->env = init_env(sh, env);
	if (!sh->env)
		exit((perror("Error malloc for env"), free_all(sh), 1));
	increment_shlvl(sh);
	sh->fd_stdin = dup(STDIN_FILENO);
	sh->fd_stdout = dup (STDOUT_FILENO);
	tcgetattr(STDIN_FILENO, &sh->original_term);
	if (*env)
		add_colors(sh);
}
