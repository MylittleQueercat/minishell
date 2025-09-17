/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:46:06 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/17 18:44:34 by aprigent         ###   ########.fr       */
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
