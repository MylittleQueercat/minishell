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

void	update_env_value(const char *key, const char *value, t_env *env)
{
	t_cmd	cmd;

	cmd.cmd = "export";
	cmd.args = (char **)malloc(3 * sizeof(char *));
	if (!cmd.args)
	{
		ft_putstr_fd("Error: Failed to allocate memory\n", 2);
		return ;
	}
	cmd.args[0] = "export";
	cmd.args[1] = (char *)malloc(ft_strlen(key) + ft_strlen(value) + 2);
	if (!cmd.args[1])
	{
		free(cmd.args);
		ft_putstr_fd("Error: Failed to allocate memory\n", 2);
		return ;
	}
	ft_strlcpy(cmd.args[1], key, ft_strlen(key) + 1);
	ft_strlcat(cmd.args[1], "=", ft_strlen(key) + 2);
	ft_strlcat(cmd.args[1], value, ft_strlen(key) + ft_strlen(value) + 2);
	cmd.args[2] = NULL;
	cmd.argc = 2;
	ft_export(&cmd, env);
	free(cmd.args[1]);
	free(cmd.args);
}

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

static void	add_env_var(t_env *env, const char *var)
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
		ft_putstr_fd("Error: Failed to allocate memory\n", 2);
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
	int		i;
	int		j;
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
			continue ;
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
