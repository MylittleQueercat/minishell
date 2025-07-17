/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:20:17 by aprigent          #+#    #+#             */
/*   Updated: 2025/07/17 12:52:30 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_cmd *cmd, t_env *env)
{
	int	i;

	if (cmd->args[1])
	{
		printf("env: '%s': No such file or directory\n", cmd->args[1]);
		return (1);
	}
	i = 0;
	while (env->envp[i])
		printf("%s\n", env->envp[i++]);
	return (0);
}
