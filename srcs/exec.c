/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:26:30 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/30 15:08:22 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_sh *sh, t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		ft_cd(sh, cmd, sh->env);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		ft_export(sh, cmd, 1);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		ft_unset(sh, cmd, sh->env);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		ft_env(cmd, sh->env);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		ft_exit(sh, cmd);
	else
		printf("Command not found: %s\n", cmd->cmd);
}

void	exec_cmd(t_sh *sh, t_cmd *cmd)
{
	int	status;
	int	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), g_st = 1, (void)0);
	if (pid == 0)
	{
		setup_redirections(cmd);
		cmd->path = get_cmd_path(sh, sh->env->path, cmd, -1);
		if (!cmd->path)
		{
			printf("minishell: %s: command not found\n", cmd->cmd);
			exit((free_all(sh), 127));
		}
		execve(cmd->path, cmd->args, sh->env->envp);
		perror("execve");
		exit((free_all(sh), 126));
	}
	waitpid(pid, &status, 0);
	g_st = status >> 8;
}

void	exec_cmd_or_builtin(t_sh *sh, t_node *node)
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
				exit((free_all(sh), g_st));
			}
			waitpid(pid, &vl, 0);
			g_st = (vl >> 8);
		}
		else
			exec_builtin(sh, node->cmd);
	}
	else
		exec_cmd(sh, node->cmd);
	dup2(sh->fd_stdin, STDIN_FILENO);
	dup2(sh->fd_stdout, STDOUT_FILENO);
}

int	node_and_or_pipe(t_sh *sh, t_node *node)
{
	if (node->type == N_AND)
	{
		run_exec(sh, node->left);
		if (g_st == 0)
			run_exec(sh, node->right);
		return (1);
	}
	if (node->type == N_OR)
	{
		run_exec(sh, node->left);
		if (g_st != 0)
			run_exec(sh, node->right);
		return (1);
	}
	if (node->type == N_PIPE)
		return (fork_node(sh, node), 1);
	return (0);
}

void	run_exec(t_sh *sh, t_node *node)
{
	if (!node)
		return ;
	expander(sh, node);
	if (node->type == N_CMD)
	{
		if ((!node->exec_args || !node->exec_args[0])
			&& !node->io_list->type)
			return (g_st = 2,
				printf("minishell: syntax error: empty command\n"), (void)0);
		else if ((!node->exec_args || !node->exec_args[0])
			&& node->io_list->type && node->io_list->type != IO_HEREDOC)
			return (g_st = 0, init_cmd(sh, node), (void)0);
		if (init_cmd(sh, node) == 1)
			return (g_st = 1, (void)0);
		return (exec_cmd_or_builtin(sh, node), (void)0);
	}
	if (node_and_or_pipe(sh, node))
		return ;
	printf("Unknown node type: %d\n", node->type);
	g_st = 1;
}
