/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:23:30 by aprigent          #+#    #+#             */
/*   Updated: 2025/07/17 14:15:12 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_cmd *cmd, t_env *env)
{
	char	*cwd;

	if (!cmd->args[1])
	{
		printf("cd: No such file or directory\n");
		return (1);
	}
	if (chdir(cmd->args[1]) != 0)
	{
		perror("cd");
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return (1);
	}
	env->pwd = ft_strdup(cwd);
	free(cwd);
	if (!env->pwd)
		ft_putstr_fd("Error: Failed to update PWD.\n", 2);
	return (0);
}
