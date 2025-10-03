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

char	*is_path(t_sh *sh)
{
	char	*path;

	path = get_env_value("PATH", sh->env->envp);
	if (!path || !*path)
		return (NULL);
	return (path);
}

int	add_ls_colors(t_sh *sh, t_cmd *cmd)
{
	if (!ft_strncmp(cmd->cmd, "ls", 2) || !ft_strncmp(cmd->cmd, "/bin/ls", 7))
	{
		cmd->argc = count_args(cmd->args);
		cmd->args[cmd->argc++] = "--color=auto";
		cmd->args = a_realloc(sh->a, cmd->args, sizeof(char *) * cmd->argc,
				sizeof(char *) * (cmd->argc + 1));
		if (!cmd->args)
			return (perror("malloc"), 1);
		cmd->args[cmd->argc] = NULL;
	}
	return (0);
}

char	*get_cmd_path(t_sh *sh, t_cmd *cmd, int i)
{
	char	*path;
	char	**paths;

	if (add_ls_colors(sh, cmd) == 1)
		return (NULL);
	if (cmd->cmd[0] == '/' || cmd->cmd[0] == '.')
		return (abs_path(sh, cmd->cmd));
	path = is_path(sh);
	if (!path)
		return (print_fd(": No such file or directory\n", cmd->cmd, 2), NULL);
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
	return (print_fd(": command not found\n", cmd->cmd, 2), NULL);
}
