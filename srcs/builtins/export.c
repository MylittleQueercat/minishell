/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:16:58 by aprigent          #+#    #+#             */
/*   Updated: 2025/07/17 16:37:59 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_env(char **envp)
{
	int		i;
	int		j;
	char	*temp;
	size_t	len;

	i = 0;
	while (envp[i])
	{
		j = i + 1;
		while (envp[j])
		{
			len = ft_strlen(envp[i]);
			if (ft_strncmp(envp[i], envp[j], len) > 0)
			{
				temp = envp[i];
				envp[i] = envp[j];
				envp[j] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	print_export(t_env *env)
{
	char	**env_cpy;
	int		i;

	i = 0;
	while (env->envp[i])
		i++;
	env_cpy = (char **)malloc(sizeof(char *) * (i + 1));
	env_cpy[i] = NULL;
	while (--i >= 0)
		env_cpy[i] = ft_strdup(env->envp[i]);
	sort_env(env_cpy);
	i = 0;
	while (env_cpy[i])
	{
		if (ft_strchr(env_cpy[i], '='))
		{
			printf("declare -x %s\n", env_cpy[i]);
		}
		else
		{
			printf("declare -x %s=\"\"\n", env_cpy[i]);
		}
		i++;
	}
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

	if (!cmd->args[1])
	{
		print_export(env);
		return (0);
	}
	i = 1;
	while (cmd->args[i])
	{
		if (ft_strchr(cmd->args[i], '='))
			add_env_var(env, cmd->args[i]);
		else
			printf("export: '%s': not a valid identifier\n", cmd->args[i]);
		i++;
	}
	return (0);
}
