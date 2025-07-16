/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:26:30 by aprigent          #+#    #+#             */
/*   Updated: 2025/07/16 20:23:10 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* * exec.c
 * This file contains the functions responsible for executing commands in the shell.
 * It handles external commands, and pipelines. (pipelines not very clean yet)
 * Does not handle built-in commands yet, but will be implemented in the future.
 */

int	exec_builtin(t_cmd *cmd, t_env *env)
{
	// Placeholder for executing a builtin command
	// This function should handle built-in commands like cd, echo, etc.
	// For now, we just return a success code.
	(void)cmd;
	(void)env;
	return (1);
}

int	exec_external(t_cmd *cmd, t_env *env)
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
	if (WIFEXITED(status))
		return WEXITSTATUS(status);
	return (1);
}

int	exec_pipe(t_cmd *cmd, t_env *env)
{
	// Placeholder for executing a pipeline of commands
	// This function should handle multiple commands connected by pipes.
	// For now, we just return a success code.
	(void)cmd;
	(void)env;
	return (1);
}

int	exec_cmd(t_cmd *cmd, t_env *env)
{
	if (cmd->type == CMD_BUILTIN)
		return (exec_builtin(cmd, env));
	else if (cmd->type == CMD_EXTERNAL)
		return (exec_external(cmd, env));
	else if (cmd->type == CMD_PIPE)
		return (exec_pipe(cmd, env));
	else
		return (0);
}
