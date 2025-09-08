/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:02:48 by aprigent          #+#    #+#             */
/*   Updated: 2025/07/16 16:39:59 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* * Initializes the environment variables from the provided envp array.
 * Allocates memory for the environment structure and its members.
 * Sets the PATH and PWD variables based on the envp array.
 * Handles memory allocation errors gracefully.
 */

void	get_env(t_env *env, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	env->envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env->envp)
	{
		perror("Failed to allocate memory for environment variables");
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (envp[++i])
	{
		env->envp[i] = ft_strdup(envp[i]);
		if (!env->envp[i])
		{
			while (i > 0)
				free(env->envp[i-- - 1]);
			free(env->envp);
			perror("Failed to initialize environment");
			exit(EXIT_FAILURE);
		}
	}
	env->envp[i] = NULL;
}

void	set_env(t_env *env)
{
	int		i;

	i = -1;
	while (env->envp[++i])
	{
		if (ft_strncmp(env->envp[i], "PATH=", 5) == 0)
		{
			env->path = ft_strdup(env->envp[i] + 5);
			if (!env->path)
			{
				perror("Failed to duplicate PATH variable");
				exit(EXIT_FAILURE);
			}
		}
		if (ft_strncmp(env->envp[i], "PWD=", 4) == 0)
		{
			env->pwd = ft_strdup(env->envp[i] + 4);
			if (!env->pwd)
			{
				perror("Failed to duplicate PWD variable");
				exit(EXIT_FAILURE);
			}
		}
	}
}

t_env *init_env(char **envp)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	ft_bzero(env, sizeof(t_env));
	if (!env)
		exit_perror(env, "Failed to allocate memory for environment");
	get_env(env, envp);
	if (!env->envp)
		exit_perror(env, "Failed to initialize environment variables");
	set_env(env);
	if (!env->path || !env->pwd || !env->oldpwd)
		exit_perror(env, "Failed to set essential environment variables");
	return (env);
}

void	free_env(t_env *env)
{
	int	i;

	if (!env)
		return;
	if (env->envp)
	{
		i = 0;
		while (env->envp[i])
		{
			free(env->envp[i]);
			i++;
		}
		free(env->envp);
	}
	if (env->path)
		free(env->path);
	if (env->pwd)
		free(env->pwd);
	if (env->oldpwd)
		free(env->oldpwd);
	free(env);
}
