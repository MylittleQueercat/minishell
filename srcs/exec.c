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

/* * exec.c
 * This file contains the functions responsible for executing commands in the shell.
 * It handles external commands, and pipelines. (pipelines not very clean yet)
 * Does not handle all built-in commands yet, but will be implemented in the future.
 */

int	exec_builtin(t_cmd *cmd, t_env *env)
{
	if (ft_strncmp(cmd->cmd, "echo", 4) == 0)
		return (ft_echo(cmd));
	else if (ft_strncmp(cmd->cmd, "env", 3) == 0)
		return (ft_env(cmd, env));
	else if (ft_strncmp(cmd->cmd, "pwd", 3) == 0)
		return (ft_pwd(cmd));
	else if (ft_strncmp(cmd->cmd, "cd", 2) == 0)
		return (ft_cd(cmd, env));
	else if (ft_strncmp(cmd->cmd, "export", 6) == 0)
		return (ft_export(cmd, env));
	else if (ft_strncmp(cmd->cmd, "unset", 5) == 0)
		return (ft_unset(cmd, env));
	printf("Command not found: %s\n", cmd->cmd);
	return (1);
}

int	exec_cmd(t_cmd *cmd, t_env *env, int i, int n)
{
	int	status;
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (0);
	}
	if (pid == 0)
	{
		if (n > 1)
			setup_pipe(cmd->pipes, i, n, cmd);
		cmd->path = get_cmd_path(env->path, cmd->cmd);
		if (!cmd->path)
		{
			printf("Command not found: %s\n", cmd->cmd);
			exit(EXIT_FAILURE);
		}
		execve(cmd->path, cmd->args, env->envp);
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

int	exec_pipe_cmd(t_node *tree, t_env *env)
{
	(void)env;
	(void)tree;
	return (0);
}

void	print_ast(t_node *node)
{
	if (!node)
		return ;
	printf("Node Type: %d\n", node->type);
	if (node->exec_args)
	{
		printf("Exec Args: ");
		for (int i = 0; node->exec_args[i]; i++)
			printf("%s ", node->exec_args[i]);
		printf("\n");
	}
	print_ast(node->left);
	print_ast(node->right);
}

/*
void	run_exec(t_minishell *sh)
{
	sh->tree->cmd = malloc(sizeof(t_cmd));
	ft_bzero(sh->tree->cmd, sizeof(t_cmd));
	if (!sh->tree->cmd)
		return (printf("Error allocating memory for command\n"), (void)0);
	if (sh->tree->type == N_PIPE)
		execute_pipeline(sh, sh->tree, 0, count_pipes(sh->tree) + 1);
	else if (sh->tree->type == N_CMD && sh->tree->exec_args)
	{
		sh->tree->cmd->cmd = sh->tree->exec_args[0];
		sh->tree->cmd->args = sh->tree->exec_args;
		if (is_builtin(sh->tree->cmd->cmd))
			sh->exit_s = exec_builtin(sh->tree->cmd, sh->env);
		else
			sh->exit_s = exec_cmd(sh->tree->cmd, sh->env, 0, 0);
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
