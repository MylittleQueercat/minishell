/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_updated.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:48:42 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/13 21:48:20 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(const char *name, char **envp)
{
	int		i;
	size_t	len;

	if (!name || !envp)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	update_envp(t_env *env)
{
	t_envl	*current;
	int		i;
	size_t	size;

	i = 0;
	size = 0;
	current = env->envl;
	while (current && ++size)
		current = current->next;
	free(env->envp);
	env->envp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!env->envp)
		return (printf("Error: Failed to allocate memory for env array.\n"), 1);
	current = env->envl;
	while (current)
	{
		env->envp[i] = ft_strjoin(current->name, "=");
		env->envp[i] = strjoin_free_s1(env->envp[i], current->value);
		if (!env->envp[i])
			return (printf("Error: Failed to duplicate env variable.\n"), 1);
		i++;
		current = current->next;
	}
	env->envp[i] = NULL;
	return (0);
}

void	change_env_var(t_env *env, const char *var)
{
	t_envl	*current;
	char	*new_value;
	int		len;
	char	*error_msg;

	current = env->envl;
	error_msg = "Error: Failed to duplicate environment variable value.\n";
	while (current)
	{
		len = ft_strlen(current->name);
		if (ft_strncmp(current->name, var, len) == 0
				&& (var[len] == '=' || var[len] == '\0'))
		{
			if (var[len] == '=')
			{
				new_value = ft_strdup(var + len + 1);
				if (!new_value)
					return (printf("%s", error_msg), (void)0);
				free(current->value);
				current->value = new_value;
			}
			return ;
		}
		current = current->next;
	}
}

static int	add_env_var(t_env *env, const char *var)
{
	t_envl	*new;
	char	*equal_sign;
	char	*err_m;

	err_m = "Error: Failed to allocate memory for new environment variable.\n";
	new = (t_envl *)malloc(sizeof(t_envl));
	if (!new)
		return (printf("%s", err_m), 0);
	equal_sign = ft_strchr(var, '=');
	if (equal_sign)
	{
		new->name = ft_substr(var, 0, equal_sign - var);
		new->value = ft_strdup(equal_sign + 1);
	}
	else
	{
		new->name = ft_strdup(var);
		new->value = NULL;
	}
	if (!new->name || (equal_sign && !new->value))
		return (free(new->name), free(new->value),
			printf("%s", err_m), free(new), 0);
	new->next = env->envl;
	env->envl = new;
	return (1);
}

int	ft_export(t_minishell *sh, t_cmd *cmd)
{
	int		i;

	if (!cmd->args[1])
		return (print_sorted_env(sh->env, -1), 0);
	i = 1;
	while (cmd->args[i])
	{
		if (is_valid_identifier(cmd->args[i]) == 0)
		{
			printf("export: '%s': not a valid identifier\n", cmd->args[i]);
			return (1);
		}
		else
		{
			if (var_exists(sh->env, cmd->args[i]) == 1)
				change_env_var(sh->env, cmd->args[i]);
			else
			{
				if (add_env_var(sh->env, cmd->args[i]) == 0)
					return (1);
			}
		}
		i++;
	}
	return (update_envp(sh->env));
}
