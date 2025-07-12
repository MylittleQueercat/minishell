/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:26:30 by aprigent          #+#    #+#             */
/*   Updated: 2025/07/12 15:28:36 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_cmd *cmd, char **env)
{
	if (cmd->type == CMD_BUILTIN)
		return (exec_builtin(cmd, env));
	else if (cmd->type == CMD_EXTERNAL)
		return (exec_external(cmd, env));
	else if (cmd->type == CMD_PIPELINE)
		return (exec_pipeline(cmd, env));
	else
		return (ERROR);
}
