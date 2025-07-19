/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:50:17 by aprigent          #+#    #+#             */
/*   Updated: 2025/07/18 12:07:45 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_var(t_cmd *cmd, t_env *env, int i)
{
	int	j;

	j = 0;
	while (env->envp[j])
	{
		if (ft_strncmp(env->envp[j], cmd->args[i], ft_strlen(cmd->args[i])) == 0
			&& env->envp[j][ft_strlen(cmd->args[i])] == '=')
		{
			free(env->envp[j]);
			while (env->envp[j + 1])
			{
				env->envp[j] = env->envp[j + 1];
				j++;
			}
			env->envp[j] = NULL;
			return (1);
		}
		j++;
	}
	return (0);
}

int	ft_unset(t_cmd *cmd, t_env *env)
{
	int	size;
	int	count;
	int	i;

	i = 1;
	if (!cmd->args[i])
		return (1);
	size = 0;
	while (env->envp[size])
		size++;
	count = 0;
	while (cmd->args[i])
	{
		count += unset_var(cmd, env, i);
		i++;
	}
	size = (size + 1) * sizeof(char *);
	env->envp = ft_realloc(env->envp, size, (size - count * sizeof(char *)));
	return (0);
}
