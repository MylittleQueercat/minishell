/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:26:30 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/08 00:47:14 by aprigent         ###   ########.fr       */
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
