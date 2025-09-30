/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 00:36:50 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/20 08:05:51 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_sh *sh, t_node *node, int *fd, int n)
{
	default_signals();
	if (n == 1)
		dup2(fd[1], STDOUT_FILENO);
	else if (n == 0)
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (n == 1)
		exit((run_exec(sh, node->left), free_all(sh), g_st));
	else if (n == 0)
		exit((run_exec(sh, node->right), free_all(sh), g_st));
}

void	fork_node(t_sh *sh, t_node *node)
{
	int	pid[2];
	int	fd[2];
	int	status[2];

	if (pipe(fd) == -1)
		return (perror("pipe"), g_st = 1, (void)0);
	pid[0] = fork();
	if (pid[0] < 0)
		return (perror("fork"), g_st = 1, (void)0);
	if (pid[0] == 0)
		child_process(sh, node, fd, 0);
	pid[1] = fork();
	if (pid[1] < 0)
		return (perror("fork"), g_st = 1, (void)0);
	if (pid[1] == 0)
		child_process(sh, node, fd, 1);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[1], &status[1], 0);
	waitpid(pid[0], &status[0], 0);
	if ((status[1] & 0x7F) == 0)
		g_st = (status[1] >> 8) & 0xFF;
	else
		g_st = 128 + (status[1] & 0x7F);
}
