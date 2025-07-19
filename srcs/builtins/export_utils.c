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
	i = -1;
	while (env_cpy[++i])
	{
		if (ft_strchr(env_cpy[i], '='))
			printf("declare -x %s\n", env_cpy[i]);
		else
			printf("declare -x %s=\"\"\n", env_cpy[i]);
	}
	while (i >= 0)
		free(env_cpy[i--]);
	free(env_cpy);
}

