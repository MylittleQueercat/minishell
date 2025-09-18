/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 00:36:50 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/18 20:06:32 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_minishell *sh, t_node *node, int *fd, int n)
{
	if (n == 1)
		dup2(fd[1], STDOUT_FILENO);
	else if (n == 0)
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (n == 1)
		exit(run_exec(sh, node->left));
	else if (n == 0)
		exit(run_exec(sh, node->right));
}
