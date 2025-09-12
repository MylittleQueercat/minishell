/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:46:06 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/11 19:32:23 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(t_node *node)
{
	int	count;

	count = 0;
	while (node)
	{
		if (node->type == N_PIPE)
			count++;
		node = node->left;
	}
	return (count);
}

void	open_redirections(t_cmd *cmd)
{
	if (cmd->infile)
	{
		cmd->in_fd = open(cmd->infile, O_RDONLY);
		if (cmd->in_fd < 0)
			return (perror(cmd->infile), (void)0);
	}
	if (cmd->outfile)
	{
		if (cmd->type == IO_OUT)
			cmd->out_fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (cmd->type == IO_ADD_END)
			cmd->out_fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->out_fd < 0)
		{
			if (cmd->in_fd != -1)
				close(cmd->in_fd);
			return (perror(cmd->outfile), (void)0);
		}
	}
}
