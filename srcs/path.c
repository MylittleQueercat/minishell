/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:43:18 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/20 07:59:16 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*abs_path(t_sh *sh, char *cmd)
{
	if (!access(cmd, X_OK))
		return (a_strdup(sh->a, cmd));
	return (NULL);
}

char	*get_cmd_path(t_sh *sh, char *path, t_cmd *cmd, int i)
{
	char	**paths;

	if (!ft_strncmp(cmd->cmd, "ls", 2) || !ft_strncmp(cmd->cmd, "/bin/ls", 7))
	{
		cmd->argc = count_args(cmd->args);
		cmd->args[cmd->argc++] = "--color=auto";
		cmd->args = a_realloc(sh->a, cmd->args, sizeof(char *) * cmd->argc,
				sizeof(char *) * (cmd->argc + 1));
		cmd->args[cmd->argc] = NULL;
	}
	if (cmd->cmd[0] == '/' || cmd->cmd[0] == '.')
		return (abs_path(sh, cmd->cmd));
	paths = a_split(sh->a, path, ':');
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		path = a_strjoin(sh->a, paths[i], "/");
		path = a_strjoin(sh->a, path, cmd->cmd);
		if (!access(path, X_OK))
			return (path);
	}
	return (NULL);
}
