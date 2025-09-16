/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:46:06 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/16 17:43:49 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_output(const char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0 || ft_strncmp(cmd, "env", 3) == 0 ||
		ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	return (0);
}

void	close_all_pipes(int **pipes, int i, int n)
{
	while (i < n)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

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
	if (cmd->infile && cmd->type != IO_HEREDOC)
	{
		cmd->in_fd = open(cmd->infile, O_RDONLY);
		if (cmd->in_fd < 0)
			return (perror(cmd->infile), (void)0);
	}
	else if (cmd->infile && cmd->type == IO_HEREDOC)
	{
		cmd->in_fd = open(".heredoc_tmp", O_RDONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->in_fd < 0)
			return (perror(".heredoc_tmp"), (void)0);
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

void	add_colors(t_minishell *sh)
{
	char	*colors[3];
	t_cmd	cmd;

	colors[0] = "export";
	colors[1] = LS_COLORS;
	colors[2] = NULL;
	cmd.cmd = *colors;
	cmd.args = colors;
	ft_export(sh, &cmd);
}
