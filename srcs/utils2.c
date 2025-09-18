/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:46:06 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/18 21:22:07 by aprigent         ###   ########.fr       */
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

void	setup_redirections(t_cmd *cmd)
{
	if (cmd->in_fd != -1)
	{
		dup2(cmd->in_fd, STDIN_FILENO);
		close(cmd->in_fd);
	}
	if (cmd->out_fd != -1)
	{
		dup2(cmd->out_fd, STDOUT_FILENO);
		close(cmd->out_fd);
	}
}
