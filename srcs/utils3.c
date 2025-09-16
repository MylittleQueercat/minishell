/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:59:34 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/16 18:23:15 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_io(t_node *node, t_cmd *cmd)
{
	t_io_node	*io;

	io = node->io_list;
	while (io)
	{
		io->exec_value = ft_split(io->raw_value, ' ');
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
	open_redirections(cmd);
}
