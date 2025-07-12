/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:26:30 by aprigent          #+#    #+#             */
/*   Updated: 2025/07/12 17:57:54 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		char *path = get_path(env, cmd->cmd);
		if (!path)
		{
			printf("Command not found: %s\n", cmd->cmd);
			exit(EXIT_FAILURE);
		}
		execve(path, cmd->args, env->envp);
		perror("execve");
		free((free(path), exit(EXIT_FAILURE), NULL));
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
