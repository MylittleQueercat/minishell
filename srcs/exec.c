/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:26:30 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/18 22:13:01 by aprigent         ###   ########.fr       */
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

int	exec_cmd(t_minishell *sh, t_cmd *cmd)
{
	int	status;
	int	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		setup_redirections(cmd);
		cmd->path = get_cmd_path(sh->env->path, cmd, -1);
		if (!cmd->path)
		{
			printf("minishell: %s: command not found\n", cmd->cmd);
			exit(127);
		}
		execve(cmd->path, cmd->args, sh->env->envp);
		perror("execve");
		exit((free(cmd->path), 126));
	}
	waitpid(pid, &status, 0);
	sh->exit_s = status >> 8;
	return (sh->exit_s);
}

int	exec_cmd_or_builtin(t_minishell *sh, t_node *node)
{
	int	vl;
	int	pid;

	setup_redirections(node->cmd);
	if (is_builtin(node->cmd->cmd))
	{
		if (node->is_in_pipe == 1 && is_builtin_output(node->cmd->cmd))
		{
			pid = fork();
			if (pid == 0)
			{
				exec_builtin(sh, node->cmd);
				exit(sh->exit_s);
			}
			waitpid(pid, &vl, 0);
			sh->exit_s = vl >> 8;
		}
		else
			sh->exit_s = exec_builtin(sh, node->cmd);
	}
	else
		sh->exit_s = exec_cmd(sh, node->cmd);
	dup2(sh->fd_stdin, STDIN_FILENO);
	dup2(sh->fd_stdout, STDOUT_FILENO);
	return (sh->exit_s);
}

int	fork_node(t_minishell *sh, t_node *node)
{
	int	pid[2];
	int fd[2];
	int	status[2];

	if (pipe(fd) == -1)
		return (perror("pipe"), -1);
	pid[0] = fork();
	if (pid[0] < 0)
		return (perror("fork"), -1);
	if (pid[0] == 0)
		child_process(sh, node, fd, 0);
	pid[1] = fork();
	if (pid[1] < 0)
		return (perror("fork"), -1);
	if (pid[1] == 0)
		child_process(sh, node, fd, 1);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	if ((status[1] & 0x7F) == 0)
		return (sh->exit_s = (status[1] >> 8) & 0xFF);
	else
		return (sh->exit_s = 128 + (status[1] & 0x7F));
}

int	run_exec(t_minishell *sh, t_node *node)
{
	if (node->type == N_CMD)
	{
		if (!node->exec_args || !node->exec_args[0])
			return (0);
		return (init_cmd(sh, node), exec_cmd_or_builtin(sh, node));
	}
	if (node->type == N_AND)
	{
		g_st = run_exec(sh, node->left);
		if (g_st == 0)
			g_st = run_exec(sh, node->right);
		return (g_st);
	}
	if (node->type == N_OR)
	{
		g_st = run_exec(sh, node->left);
		if (g_st != 0)
			g_st = run_exec(sh, node->right);
		return (g_st);
	}
	if (node->type == N_PIPE)
		return (fork_node(sh, node));
	printf("Unknown node type: %d\n", node->type);
	return (1);
}
