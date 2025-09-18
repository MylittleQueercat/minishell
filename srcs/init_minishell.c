/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 18:09:12 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/18 21:55:31 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(t_minishell *sh, char **env)
{
	ft_bzero(sh, sizeof(*sh));
	sh->env = init_env(env);
	sh->fd_stdin = dup(STDIN_FILENO);
	sh->fd_stdout = dup (STDOUT_FILENO);
	tcgetattr(STDIN_FILENO, &sh->original_term);
	if (*env)
		add_colors(sh);
}
