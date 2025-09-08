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

void	close_pipes(int **pipes, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

static void	setup_pipe(int **pipes, int i, int n, t_cmd *cmd)
{
	if (i == 0)
	{
		dup2(pipes[i][1], STDOUT_FILENO);
	}
	else if (i == n - 1)
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
	}
	else
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		dup2(pipes[i][1], STDOUT_FILENO);
	}
	cmd->pipes = pipes[i];
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
		node = node->right;
	}
	return (count);
}

void	execute_pipeline(t_minishell *sh, t_node *node)
{
	int		**pipes;
	int		n;
	int		i;
	pid_t	pid;

	n = count_pipes(node) + 1;
	pipes = create_pipes(n);
	if (!pipes)
		return (sh->exit_s = 1, (void)0);
	while (node && node->type == N_PIPE)
	{
		node->cmd = malloc(sizeof(t_cmd));
		if (!node->cmd)
			return (perror("malloc"), free_pipes(pipes, n - 1), (void)0);
		ft_bzero(node->cmd, sizeof(t_cmd));
		node = node->right;
	}
	i = -1;
	while (++i < n)
	{
		pid = fork();
		if (pid < 0)
			return (perror("fork"), free_pipes(pipes, n - 1));
		if (pid == 0)
		{
			setup_pipe(pipes, i, n, node->cmd);
			node->cmd->cmd = node->exec_args[0];
			node->cmd->args = node->exec_args;
			exec_cmd(node->cmd, sh->env);
			close_pipes(pipes, n - 1);
			exit(sh->exit_s);
		}
		if (node->right)
			node = node->right;
		else
			break ;
	}
	close_pipes(pipes, n - 1);
	free_pipes(pipes, n - 1);
	while (n-- > 0)
		waitpid(-1, &sh->exit_s, 0);
	if (WIFEXITED(sh->exit_s))
		sh->exit_s = WEXITSTATUS(sh->exit_s);
}
