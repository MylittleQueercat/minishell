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

char	*get_cmd_path(char *path, char *cmd)
{
	char	**paths;
	int		i;

	i = 0;
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		path = paths[i];
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cmd);
		if (!access(path, X_OK))
			return (free_array(paths), path);
		free(path);
		i++;
	}
	return (free_array(paths), NULL);
}
