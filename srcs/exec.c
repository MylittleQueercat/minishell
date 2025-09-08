/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:26:30 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/02 19:09:53 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* * exec.c
 * This file contains the functions responsible for executing commands in the shell.
 * It handles external commands, and pipelines.
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
	else if (ft_strncmp(cmd->cmd, "exit", 4) == 0)
		return (ft_exit(cmd, env));
	printf("Command not found: %s\n", cmd->cmd);
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
		cmd->path = get_cmd_path(env->path, cmd);
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
	if (pid > 0)
		return (status >> 8); // Return the exit status of the child process
	return (1);
}

int	exec_pipe(t_cmd *cmd, t_env *env)
{
	int		pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (0);
	}
	if (pid == 0)
	{
		cmd->path = get_cmd_path(env->path, cmd);
		if (!cmd->path)
		{
			printf("Command not found: %s\n", cmd->cmd);
			exit(EXIT_FAILURE);
		}
	}
	return (1);
}
