/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 00:36:50 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/08 00:46:38 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipe(int *pipes, int i, int n, t_cmd *cmd)
{
	if (i == 0)
		dup2(pipes[1], STDOUT_FILENO);
	else if (i == n - 1)
		dup2(pipes[0], STDIN_FILENO);
	else
	{
		dup2(pipes[0], STDIN_FILENO);
		dup2(pipes[1], STDOUT_FILENO);
	}
	close(pipes[0]);
	close(pipes[1]);
	cmd->pipes = pipes;
}

static int	**create_pipes(int n)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * (n - 1));
	if (!pipes)
		return (NULL);
	i = -1;
	while (++i < n - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (free_pipes(pipes, i), NULL);
		if (pipe(pipes[i]) == -1)
			return (perror("pipe"), free_pipes(pipes, i + 1), NULL);
	}
	return (pipes);
}

int	count_pipes(t_node *node)
{
	int	count;

	count = 0;
	while (node && node->type == N_PIPE)
	{
		count++;
		node = node->left;
	}
	return (count);
}

int	execute_pipeline(t_minishell *sh, t_node *node, int i, int nb_pipes)
{
	if (i == 0)
	{
		sh->pipes = create_pipes(nb_pipes);
		if (!sh->pipes)
			return (perror("Error creating pipes"), -1);
	}
	if (node->left->type == N_PIPE)
	{
		if (execute_pipeline(sh, node->left, i + 1, nb_pipes) == -1)
			return (-1);
	}
	else if (node->left->type == N_CMD)
	{
		node->left->cmd = malloc(sizeof(t_cmd));
		if (!node->left->cmd)
			return (perror("malloc"), free_pipes(sh->pipes, nb_pipes - 1), -1);
		ft_bzero(node->left->cmd, sizeof(t_cmd));
		node->left->cmd->args = node->left->exec_args;
		node->left->cmd->cmd = node->left->exec_args[0];
		node->left->cmd->pipes = sh->pipes[i];
		exec_cmd(node->left->cmd, sh->env, i, nb_pipes);
	}
	if (node->right->type == N_CMD)
	{
		node->right->cmd = malloc(sizeof(t_cmd));
		if (!node->right->cmd)
			return (perror("malloc"), free_pipes(sh->pipes, nb_pipes - 1), -1);
		ft_bzero(node->right->cmd, sizeof(t_cmd));
		node->right->cmd->args = node->right->exec_args;
		node->right->cmd->cmd = node->right->exec_args[0];
		node->right->cmd->pipes = sh->pipes[i];
		exec_cmd(node->right->cmd, sh->env, i, nb_pipes);
	}
	return (0);
}
