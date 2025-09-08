/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:43:18 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/02 23:07:02 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*abs_path(char *cmd)
{
	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	return (NULL);
}

char	*get_cmd_path(char *path, t_cmd *cmd)
{
	char	**paths;
	int		i;

	i = -1;
	if (!ft_strncmp(cmd->cmd, "ls", 2) || !ft_strncmp(cmd->cmd, "/bin/ls", 7))
	{
		cmd->args[cmd->argc++] = "--color=auto";
		cmd->args = ft_realloc(cmd->args, sizeof(char *) * cmd->argc,
				sizeof(char *) * (cmd->argc + 1));
		cmd->args[cmd->argc] = NULL;
	}
	if (cmd->cmd[0] == '/' || cmd->cmd[0] == '.')
		return (abs_path(cmd->cmd));
	paths = ft_split(path, ':');
	while (paths && paths[++i])
	{
		path = paths[i];
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cmd->cmd);
		if (!access(path, X_OK))
			return (free_array(paths), path);
		free(path);
	}
	return (free_array(paths), NULL);
}
