/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:24:32 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/18 21:55:08 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	var_exists(t_env *env, const char *var)
{
	t_envl	*current;
	int		len;

	current = env->envl;
	while (current)
	{
		len = ft_strlen(current->name);
		if (ft_strncmp(current->name, var, len) == 0
			&& (var[len] == '=' || var[len] == '\0'))
			return (1);
		current = current->next;
	}
	return (0);
}

static void	sort_envp(char **envp)
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

static void	print_envp(t_env *env, int flag)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	while (env->envp[i])
	{
		p = ft_strchr(env->envp[i], '=');
		j = (int)(p - env->envp[i]);
		if (p && flag == -1)
			printf("declare -x %.*s=\"%s\"\n", j, env->envp[i], p + 1);
		else if (p && flag == 1)
			printf("%s\n", env->envp[i]);
		else if (!p && flag == -1)
			printf("declare -x %s\n", env->envp[i]);
		else if (!p && flag == 1 && ft_strchr(env->envp[i], '=') != NULL)
			printf("%s\n", env->envp[i]);
		i++;
	}
}

void	print_sorted_env(t_env *env, int flag)
{
	sort_envp(env->envp);
	print_envp(env, flag);
}
