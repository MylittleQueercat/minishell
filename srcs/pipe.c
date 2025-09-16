/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 00:36:50 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/16 18:15:26 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(int **pipes, int i, int n)
{
	if (i == 0)
	{
		close(pipes[i][0]);
		close_all_pipes(pipes, i + 1, n);
	}
	if (i == n)
	{
		close(pipes[i - 1][1]);
		close_all_pipes(pipes, 0, i - 1);
	}
	if (i > 0 && i < n)
	{
		close(pipes[i - 1][1]);
		close(pipes[i][0]);
		close_all_pipes(pipes, 0, i - 1);
		close_all_pipes(pipes, i + 1, n);
	}
}

void	setup_pipes(int **pipes, int i, int n, t_cmd *cmd)
{
	if (i == 0 && n > 0)
	{
		dup2(pipes[i][1], STDOUT_FILENO);
		close_pipes(pipes, i, n);
	}
	else if (i == n && n > 0)
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		close_pipes(pipes, i, n);
	}
	else if (i > 0 && i < n)
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		dup2(pipes[i][1], STDOUT_FILENO);
		close_pipes(pipes, i, n);
	}
	if (cmd->in_fd != -1)
	{
		dup2(cmd->in_fd, STDIN_FILENO);
		close(cmd->in_fd);
	}
	if (cmd->out_fd != -1)
	{
		dup2(cmd->out_fd, STDOUT_FILENO);
		close(cmd->out_fd);
	}
}

static int	**create_pipes(int n)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * n);
	if (!pipes)
		return (NULL);
	i = -1;
	while (++i < n)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (free_pipes(pipes, i), NULL);
		if (pipe(pipes[i]) == -1)
			return (perror("pipe"), free_pipes(pipes, i + 1), NULL);
	}
	return (pipes);
}

int	exec_pipeline(t_minishell *sh, t_node *node, int *i, int n)
{
	sh->nb_pipes = n;
	if (*i == 0)
	{
		sh->pipes = create_pipes(sh->nb_pipes);
		if (!sh->pipes)
			return (perror("Error creating pipes"), -1);
	}
	if (node->left->type == N_PIPE)
	{
		if (exec_pipeline(sh, node->left, i, sh->nb_pipes) == -1)
			return (-1);
	}
	else if (node->left->type == N_CMD)
	{
		node->left->is_in_pipe = 1;
		if (init_cmd(sh, node->left) == -1)
			return (perror("malloc"), -1);
		exec_cmd_or_builtin(sh, node->left, (*i)++, sh->nb_pipes);
	}
	if (node->right->type == N_CMD)
	{
		node->right->is_in_pipe = 1;
		if (init_cmd(sh, node->right) == -1)
			return (perror("malloc"), -1);
		exec_cmd_or_builtin(sh, node->right, (*i)++, sh->nb_pipes);
	}
	return (0);
}
