/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:16:58 by aprigent          #+#    #+#             */
/*   Updated: 2025/07/18 14:37:12 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_env_var(char **envp, const char *var, int index)
{
	char	*new_var;

	new_var = ft_strdup(var);
	if (!new_var)
	{
		ft_putstr_fd("Error: Failed to duplicate environment variable.\n", 2);
		return ;
	}
	free(envp[index]);
	envp[index] = new_var;
}

static void add_env_var(t_env *env, const char *var)
{
	int		i;
	size_t	size;

	i = 0;
	while (env->envp[i])
		i++;
	size = sizeof(char *) * (i + 1);
	env->envp = (char **)ft_realloc(env->envp, size, size + sizeof(char *));
	if (!env->envp)
	{
		ft_putstr_fd("Error: Failed to allocate memory for environment variable.\n", 2);
		return ;
	}
	env->envp[i] = ft_strdup(var);
	if (!env->envp[i])
	{
		ft_putstr_fd("Error: Failed to duplicate environment variable.\n", 2);
		return ;
	}
	env->envp[i + 1] = NULL;
}

int	ft_export(t_cmd *cmd, t_env *env)
{
	int	i;
	int	j;
	char	*p;
	int		flag;

	if (!cmd->args[1])
	{
		print_export(env);
		return (0);
	}
	i = 0;
	while (cmd->args[++i])
	{
		p = ft_strchr(cmd->args[i], '=');
		if (!p)
		{
			printf("export: '%s': not a valid identifier\n", cmd->args[i]);
			continue;
		}
		j = -1;
		flag = 0;
		while (env->envp[++j])
		{
			if (ft_strncmp(env->envp[j], cmd->args[i], p - cmd->args[i]) == 0
				&& env->envp[j][p - cmd->args[i]] == '=')
			{
				change_env_var(env->envp, cmd->args[i], j);
				flag = 1;
				break ;
			}
		}
		if (flag == 0)
			add_env_var(env, cmd->args[i]);
	}
	return (0);
}
