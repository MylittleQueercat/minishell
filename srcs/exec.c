/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:26:30 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/09 18:40:34 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_minishell *sh, t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		return (ft_echo(cmd));
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		return (ft_cd(cmd, sh->env));
	if (ft_strcmp(cmd->cmd, "pwd") == 0)
		return (ft_pwd(cmd));
	if (ft_strcmp(cmd->cmd, "export") == 0)
		return (ft_export(cmd, sh->env));
	if (ft_strcmp(cmd->cmd, "unset") == 0)
		return (ft_unset(cmd, sh->env));
	if (ft_strcmp(cmd->cmd, "env") == 0)
		return (ft_env(cmd, sh->env));
	if (ft_strcmp(cmd->cmd, "exit") == 0)
		return (ft_exit(sh, cmd));
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
		cmd->path = get_cmd_path(sh->env->path, cmd->cmd);
		if (!cmd->path)
		{
			printf("Command not found: %s\n", cmd->cmd);
			exit(EXIT_FAILURE);
		}
		execve(cmd->path, cmd->args, sh->env->envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	if (status == 256)
		return (127);
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	exec_cmd_or_builtin(t_minishell *sh, t_cmd *cmd, int i, int n)
{
	if (is_builtin(cmd->cmd))
		return (exec_builtin(sh, cmd));
	else
		return (exec_cmd(sh, cmd, i, n));
}

/*
void	run_exec(t_minishell *sh)
{
	int	i;

	i = 0;
	sh->tree->cmd = malloc(sizeof(t_cmd));
	if (!sh->tree->cmd)
		return (printf("Error allocating memory for command\n"), (void)0);
	ft_bzero(sh->tree->cmd, sizeof(t_cmd));
	if (sh->tree->type == N_PIPE)
	{
		if (execute_pipeline(sh, sh->tree, &i, count_pipes(sh->tree)) == -1)
			return ;
	}
	if (sh->tree->type == N_AND)
	{
		if (exec_cmd_or_builtin(sh, sh->tree->left->cmd, -1, 0) == 0)
			sh->exit_s = exec_cmd_or_builtin(sh, sh->tree->right->cmd, -1, 0);
		else
			sh->exit_s = 1;
	}
	else if (sh->tree->type == N_OR)
	{
		if (exec_cmd_or_builtin(sh, sh->tree->left->cmd, -1, 0) != 0)
			sh->exit_s = exec_cmd_or_builtin(sh, sh->tree->right->cmd, -1, 0);
		else
			sh->exit_s = 0;
	}
	else if (sh->tree->type == N_CMD && sh->tree->exec_args)
	{
		sh->tree->cmd->cmd = sh->tree->exec_args[0];
		sh->tree->cmd->args = sh->tree->exec_args;
		if (is_builtin(sh->tree->cmd->cmd))
			sh->exit_s = exec_builtin(sh, sh->tree->cmd);
		else
			sh->exit_s = exec_cmd(sh, sh->tree->cmd, -1, 0);
	}
	else
	{
		if (sh->tree->type == N_CMD)
			printf("No command to execute.\n");
		else
			printf("Unsupported node type for execution.\n");
	}
}
*/

int	run_subtree(t_minishell *sh, t_node *node)
{
	t_cmd	cmd;
	int		st;

	if (!node)
		return (0);
	if (node->type == N_PIPE)
		return execute_pipeline(sh, node, 0, count_pipes(node) + 1);
	if (node->type == N_AND)
	{
		st = run_subtree(sh, node->left);
		if (st == 0) st = run_subtree(sh, node->right);
		return (st);
	}
	if (node->type == N_OR)
	{
		st = run_subtree(sh, node->left);
		if (st != 0) st = run_subtree(sh, node->right);
		return (st);
	}
	if (node->type == N_CMD)
	{
		if (!node->exec_args || !node->exec_args[0])
			return (0);
		ft_bzero(&cmd, sizeof(cmd));
		cmd.cmd  = node->exec_args[0];
		cmd.args = node->exec_args;
		if (is_builtin(cmd.cmd))
			return (exec_builtin(&cmd, sh->env));
		return (exec_cmd(&cmd, sh->env, 0, 0));
	}
	return (1);
}

void    run_exec(t_minishell *sh)
{
	t_node	*n;
	t_cmd	cmd;

	n = sh->tree;
	if (!n)
		return ;
	if (n->type == N_PIPE)
	{
		sh->exit_s = execute_pipeline(sh, n, 0, count_pipes(n) + 1);
		return ;
	}
	if (n->type == N_AND)
	{
		sh->exit_s = run_subtree(sh, n->left);
		if (sh->exit_s == 0)
			sh->exit_s = run_subtree(sh, n->right);
		return ;
	}
	if (n->type == N_OR)
	{
		sh->exit_s = run_subtree(sh, n->left);
		if (sh->exit_s != 0)
			sh->exit_s = run_subtree(sh, n->right);
		return ;
	}
	if (n->type == N_CMD)
	{
		if (!n->exec_args || !n->exec_args[0])
		{
			printf("No command to execute.\n");
			sh->exit_s = 0;
			return ;
		}
		ft_bzero(&cmd, sizeof(cmd));       
		cmd.cmd  = n->exec_args[0];
		cmd.args = n->exec_args;
		if (is_builtin(cmd.cmd))
			sh->exit_s = exec_builtin(&cmd, sh->env);
		else
			sh->exit_s = exec_cmd(&cmd, sh->env, 0, 0);
		return ;
	}
	printf("Unsupported node type for execution.\n");
	sh->exit_s = 1;
}
