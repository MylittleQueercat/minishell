/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 00:41:21 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/20 08:04:54 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_stdio(t_sh *sh)
{
	if (sh->fd_stdin != -1)
	{
		dup2(sh->fd_stdin, STDIN_FILENO);
		close(sh->fd_stdin);
		sh->fd_stdin = -1;
	}
	if (sh->fd_stdout != -1)
	{
		dup2(sh->fd_stdout, STDOUT_FILENO);
		close(sh->fd_stdout);
		sh->fd_stdout = -1;
	}
}

void	free_all(t_sh *sh)
{
	if (!sh)
		return ;
	close_stdio(sh);
	if (sh->a)
		arena_free(sh->a);
	if (sh->sh_arena)
		arena_free(sh->sh_arena);
}
