/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:48:42 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/20 08:09:15 by aprigent         ###   ########.fr       */
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

int	update_envp(t_sh *sh, t_env *env)
{
	t_envl	*current;
	int		i;
	size_t	size;

	i = 0;
	size = 0;
	current = env->envl;
	while (current && ++size)
		current = current->next;
	env->envp = (char **)arena_alloc(sh->sh_arena, (size + 1) * sizeof(char *));
	if (!env->envp)
		return (perror("malloc"), 1);
	current = env->envl;
	while (current)
	{
		env->envp[i] = a_strjoin(sh->sh_arena, current->name, "=");
		env->envp[i] = a_strjoin(sh->sh_arena, env->envp[i], current->value);
		if (!env->envp[i])
			return (perror("malloc"), 1);
		i++;
		current = current->next;
	}
	env->envp[i] = NULL;
	return (0);
}

void	change_env_var(t_sh *sh, t_env *env, const char *var)
{
	t_envl	*current;
	char	*new_value;
	int		len;

	current = env->envl;
	while (current)
	{
		len = ft_strlen(current->name);
		if (ft_strncmp(current->name, var, len) == 0
				&& (var[len] == '=' || var[len] == '\0'))
		{
			if (var[len] == '=')
			{
				new_value = a_strdup(sh->sh_arena, var + len + 1);
				if (!new_value)
					return (perror("malloc"), (void)0);
				current->value = new_value;
			}
			return ;
		}
		current = current->next;
	}
}

static int	add_env_var(t_sh *sh, t_env *env, const char *var)
{
	t_envl	*new;
	char	*equal_sign;
	char	*err_m;

	err_m = "Error: Failed to allocate memory for new environment variable.\n";
	new = (t_envl *)arena_alloc(sh->sh_arena, sizeof(t_envl));
	if (!new)
		return (printf("%s", err_m), 0);
	equal_sign = ft_strchr(var, '=');
	if (equal_sign)
	{
		new->name = a_substr(sh->sh_arena, var, 0, equal_sign - var);
		new->value = a_strdup(sh->sh_arena, equal_sign + 1);
	}
	else
	{
		new->name = a_strdup(sh->sh_arena, var);
		new->value = NULL;
	}
	if (!new->name || (equal_sign && !new->value))
		return (printf("%s", err_m), 0);
	new->next = env->envl;
	env->envl = new;
	return (1);
}

int	ft_export(t_sh *sh, t_cmd *cmd)
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
				change_env_var(sh, sh->env, cmd->args[i]);
			else
			{
				if (add_env_var(sh, sh->env, cmd->args[i]) == 0)
					return (1);
			}
		}
		i++;
	}
	return (update_envp(sh, sh->env));
}
