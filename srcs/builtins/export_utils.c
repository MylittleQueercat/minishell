/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:24:32 by aprigent          #+#    #+#             */
/*   Updated: 2025/07/18 12:24:53 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env(char **envp)
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


void	print_exp(char **env_cpy, int i)
{
	char	*equal_sign;
	char	*var_name;
	char	*var_value;

	while (env_cpy[++i])
	{
		equal_sign = ft_strchr(env_cpy[i], '=');
		var_name = ft_substr(env_cpy[i], 0, equal_sign - env_cpy[i]);
		var_value = ft_strdup(equal_sign + 1);
		if (!var_value || !var_name)
		{
			free(var_name);
			free(var_value);
			ft_putstr_fd("Error: Failed to allocate memory for env var.\n", 2);
			return ;
		}
		printf("declare -x %s=\"%s\"\n", var_name, var_value);
	}
}

void	print_export(t_env *env)
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
	print_exp(env_cpy, -1);
	while (i >= 0)
		free(env_cpy[i--]);
	free(env_cpy);
}

