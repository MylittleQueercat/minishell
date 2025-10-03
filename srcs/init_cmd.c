/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:35:18 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/30 14:34:35 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_outfile(t_cmd *cmd)
{
	if (cmd->outfile)
	{
		if (cmd->out_fd != -1)
			close(cmd->out_fd);
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

int	open_redirections(t_cmd *cmd)
{
	if (cmd->infile && cmd->type != IO_HEREDOC)
	{
		if (cmd->in_fd != -1)
			close(cmd->in_fd);
		cmd->in_fd = open(cmd->infile, O_RDONLY);
		if (cmd->in_fd < 0)
			return (perror(cmd->infile), 1);
	}
	if (open_outfile(cmd) == 1)
		return (1);
	return (0);
}

int	parse_io(t_sh *sh, t_node *node, t_cmd *cmd)
{
	t_io_node	*io;

	io = node->io_list;
	while (io)
	{
		io->exec_value = a_split(sh->a, io->raw_value, ' ');
		if (!io->exec_value)
			return (perror("malloc"), 1);
		if (io->type == IO_IN)
			cmd->infile = throw_quotes(sh, io->exec_value[0]);
		else if (io->type == IO_OUT || io->type == IO_ADD_END)
			cmd->outfile = throw_quotes(sh, io->exec_value[0]);
		cmd->type = io->type;
		if (open_redirections(cmd) == 1)
			return (1);
		io = io->next;
	}
	return (0);
}

int	init_cmd(t_sh *sh, t_node *node)
{
	t_cmd	*cmd;

	node->cmd = arena_alloc(sh->a, sizeof(t_cmd));
	if (!node->cmd)
		return (perror("malloc"), 1);
	cmd = node->cmd;
	ft_bzero(cmd, sizeof(t_cmd));
	if (node->exec_args)
	{
		cmd->cmd = node->exec_args[0];
		cmd->args = node->exec_args;
		cmd->argc = count_args(node->exec_args);
	}
	cmd->out_fd = -1;
	if (node->heredoc_fd != -1)
		cmd->in_fd = node->heredoc_fd;
	return (parse_io(sh, node, cmd));
}
