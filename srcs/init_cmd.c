/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:35:18 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/17 19:19:20 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redirections(t_minishell *sh, t_node *node, t_cmd *cmd)
{
	if (cmd->infile && cmd->type != IO_HEREDOC)
	{
		cmd->in_fd = open(cmd->infile, O_RDONLY);
		if (cmd->in_fd < 0)
			return (perror(cmd->infile), 1);
	}
	else if (cmd->infile && cmd->type == IO_HEREDOC
		&& exec_heredoc(sh, node) == 1)
		return (1);
	if (cmd->outfile)
	{
		if (cmd->type == IO_OUT)
			cmd->out_fd = open(cmd->outfile, O_WRONLY | O_CREAT
					| O_TRUNC, 0644);
		else if (cmd->type == IO_ADD_END)
			cmd->out_fd = open(cmd->outfile, O_WRONLY | O_CREAT
					| O_APPEND, 0644);
		if (cmd->out_fd < 0)
		{
			if (cmd->in_fd != -1)
				close(cmd->in_fd);
			return (perror(cmd->outfile), 1);
		}
	}
	return (0);
}

int	parse_io(t_minishell *sh, t_node *node, t_cmd *cmd)
{
	t_io_node	*io;

	io = node->io_list;
	while (io)
	{
		io->exec_value = ft_split(io->raw_value, ' ');
		if (!io->exec_value)
			return (perror("malloc"), -1);
		if (io->type == IO_IN)
			cmd->infile = io->exec_value[0];
		else if (io->type == IO_OUT)
			cmd->outfile = io->exec_value[0];
		else if (io->type == IO_HEREDOC)
			cmd->infile = io->exec_value[0];
		else if (io->type == IO_ADD_END)
			cmd->outfile = io->exec_value[0];
		cmd->type = io->type;
		io = io->next;
	}
	return (open_redirections(sh, node, cmd));
}

int	init_cmd(t_minishell *sh, t_node *node)
{
	t_cmd	*cmd;

	node->cmd = malloc(sizeof(t_cmd));
	if (!node->cmd)
		return (perror("malloc"), 1);
	cmd = node->cmd;
	ft_bzero(cmd, sizeof(t_cmd));
	cmd->cmd = node->exec_args[0];
	cmd->args = node->exec_args;
	cmd->out_fd = -1;
	cmd->in_fd = -1;
	return (parse_io(sh, node, cmd));
}
