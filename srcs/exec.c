/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:26:30 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/16 18:18:36 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_minishell *sh, t_cmd *cmd)
{
	setup_pipes(NULL, 0, -1, cmd);
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		return (ft_echo(cmd));
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		return (ft_cd(cmd, sh->env));
	if (ft_strcmp(cmd->cmd, "pwd") == 0)
		return (ft_pwd(cmd));
	if (ft_strcmp(cmd->cmd, "export") == 0)
		return (ft_export(sh, cmd));
	if (ft_strcmp(cmd->cmd, "unset") == 0)
		return (ft_unset(cmd, sh->env));
	if (ft_strcmp(cmd->cmd, "env") == 0)
		return (ft_env(cmd, sh->env));
	if (ft_strcmp(cmd->cmd, "exit") == 0)
		return (ft_exit(sh, cmd, "minishell: "));
	printf("Command not found: %s\n", cmd->cmd);
	return (1);
}

int	exec_cmd(t_minishell *sh, t_cmd *cmd, int i, int n)
{
	int	status;
	int	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		setup_pipes(sh->pipes, i, n, cmd);
		cmd->path = get_cmd_path(sh->env->path, cmd, -1);
		if (!cmd->path)
		{
			printf("Command not found: %s\n", cmd->cmd);
			exit((free_minishell(sh), 127));
		}
		execve(cmd->path, cmd->args, sh->env->envp);
		perror("execve");
		exit((free(cmd->path), free_minishell(sh), 126));
	}
	waitpid(pid, &status, 0);
	sh->exit_s = status >> 8;
	return (sh->exit_s);
}

int	exec_cmd_or_builtin(t_minishell *sh, t_node *node, int i, int n)
{
	int	vl;
	int	pid;

	if (is_builtin(node->cmd->cmd))
	{
		if (node->is_in_pipe == 1 && is_builtin_output(node->cmd->cmd))
		{
			pid = fork();
			if (pid == 0)
			{
				setup_pipes(sh->pipes, i, n, node->cmd);
				exec_builtin(sh, node->cmd);
				exit(sh->exit_s);
			}
			waitpid(pid, &vl, 0);
			sh->exit_s = vl >> 8;
			return (sh->exit_s);
		}
		else
		{
			vl = exec_builtin(sh, node->cmd);
			dup2(sh->fd_stdin, STDIN_FILENO);
			dup2(sh->fd_stdout, STDOUT_FILENO);
			return (vl);
		}
	}
	else
		return (exec_cmd(sh, node->cmd, i, n));
}

int	run_subtree(t_minishell *sh, t_node *node, t_cmd *cmd, int st)
{
	if (!node)
		return (0);
	if (node->type == N_PIPE)
		return (exec_pipeline(sh, node, 0, count_pipes(node)));
	if (node->type == N_AND)
	{
		st = run_subtree(sh, node->left, cmd, 0);
		if (st == 0)
			st = run_subtree(sh, node->right, cmd, 0);
		return (st);
	}
	if (node->type == N_OR)
	{
		st = run_subtree(sh, node->left, cmd, 0);
		if (st != 0)
			st = run_subtree(sh, node->right, cmd, 0);
		return (st);
	}
	if (node->type == N_CMD)
	{
		if (!node->exec_args || !node->exec_args[0])
			return (0);
		return (init_cmd(sh, node), exec_cmd_or_builtin(sh, node, 0, -1));
	}
	return (1);
}

void	run_exec(t_minishell *sh)
{
	t_node	*n;
	int		i;

	n = sh->tree;
	if (!n)
		return ;
	i = 0;
	if (n->type == N_PIPE)
		return (sh->exit_s = exec_pipeline(sh, n, &i, count_pipes(n)), (void)0);
	init_cmd(sh, n);
	if (n->type == N_AND)
	{
		sh->exit_s = run_subtree(sh, n->left, n->cmd, 0);
		if (sh->exit_s == 0)
			sh->exit_s = run_subtree(sh, n->right, n->cmd, 0);
		return ;
	}
	if (n->type == N_OR)
	{
		sh->exit_s = run_subtree(sh, n->left, n->cmd, 0);
		if (sh->exit_s != 0)
			sh->exit_s = run_subtree(sh, n->right, n->cmd, 0);
		return ;
	}
	if (n->type == N_CMD)
	{
		if (!n->exec_args || !n->exec_args[0])
			return (printf("No command to execute.\n"), (void)(sh->exit_s = 0));
		init_cmd(sh, n);
		return (sh->exit_s = exec_cmd_or_builtin(sh, n, 0, -1), (void)0);
	}
	printf("Unsupported node type for execution.\n");
	return (sh->exit_s = 1, (void)0);
}
