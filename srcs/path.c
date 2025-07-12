/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:43:18 by aprigent          #+#    #+#             */
/*   Updated: 2025/07/12 17:00:12 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*return_path(char *cmd, char **paths)
{
	char	*path;
	int		i;

	i = 0;
	while (paths[i])
	{
		path = paths[i];
		path = ft_strjoin(paths[i], "/");
		if (!path)
			break ;
		path = ft_strjoin(path, cmd);
		if (!path)
			break ;
		if (!access(path, X_OK))
			return (free_array(paths), path);
		free(path);
		i++;
	}
	return (free_array(paths), NULL);
}

char	*get_path(t_env *env, char *cmd)
{
	int	i;
	char	**paths;

	i = 0;
	while (env->envp[i])
	{
		if (!ft_strncmp(env->envp[i], "PATH=", 5))
			break ;
		i++;
	}
	if (!env->envp[i])
		return (NULL);
	paths = ft_split(env->envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (return_path(cmd, paths));
}
