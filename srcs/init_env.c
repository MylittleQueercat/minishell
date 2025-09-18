/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:02:48 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/18 21:39:19 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env(t_env *env, char **envp, int i)
{
	t_envl	*new;
	int		equal_pos;

	while (envp[++i])
	{
		new = (t_envl *)malloc(sizeof(t_envl));
		if (!new)
			perror_exit("Allocation error for env struct", free_env, env);
		if (!env->envl)
			env->envl = new;
		else
			get_last_envl(env->envl)->next = new;
		equal_pos = ft_strchr(envp[i], '=') - envp[i];
		if (equal_pos == -1)
			continue ;
		new->name = (char *)malloc(sizeof(char) * (equal_pos + 1));
		if (!new->name)
			perror_exit("Allocation error for env name", free_env, env);
		ft_strlcpy(new->name, envp[i], equal_pos + 1);
		new->value = ft_strdup(envp[i] + equal_pos + 1);
		if (!new->value)
			perror_exit("Allocation error for env value", free_env, env);
		new->next = NULL;
	}
}

void	set_env(t_env *env, t_envl *current)
{
	while (current)
	{
		if (ft_strcmp(current->name, "PATH") == 0)
		{
			free(env->path);
			env->path = ft_strdup(current->value);
			if (!env->path)
				perror_exit("Allocation error for PATH", free_env, env);
		}
		else if (ft_strcmp(current->name, "PWD") == 0)
		{
			free(env->pwd);
			env->pwd = ft_strdup(current->value);
			if (!env->pwd)
				perror_exit("Allocation error for PWD", free_env, env);
		}
		else if (ft_strcmp(current->name, "OLDPWD") == 0)
		{
			free(env->oldpwd);
			env->oldpwd = ft_strdup(current->value);
			if (!env->oldpwd)
				perror_exit("Allocation error for OLDPWD", free_env, env);
		}
		current = current->next;
	}
}

void	set_envp(t_env *env, int i, int size)
{
	t_envl	*current;

	current = env->envl;
	while (current)
	{
		size++;
		current = current->next;
	}
	env->envp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!env->envp)
		return ;
	current = env->envl;
	while (current)
	{
		env->envp[i] = ft_strjoin(current->name, "=");
		env->envp[i] = strjoin_free_s1(env->envp[i], current->value);
		if (!env->envp[i])
			perror_exit("Allocation error for env array", free_env, env);
		i++;
		current = current->next;
	}
	env->envp[i] = NULL;
}

void	empty_env(t_env *env)
{
	env->pwd = getcwd(NULL, 0);
	env->path = ft_strdup("");
	if (!env->pwd || !env->path)
		perror_exit("Allocation error for PWD or PATH", free_env, env);
	env->envl = malloc(sizeof(t_envl));
	if (!env->envl)
		perror_exit("Allocation error for env struct", free_env, env);
	env->envl->name = ft_strdup("PWD");
	env->envl->value = ft_strdup(env->pwd);
	env->envl->next = malloc(sizeof(t_envl));
	if (!env->envl->next || !env->envl->name || !env->envl->value)
		perror_exit("Allocation error for env struct", free_env, env);
	env->envl->next->name = ft_strdup("SHLVL");
	env->envl->next->value = ft_strdup("1");
	env->envl->next->next = NULL;
	if (!env->envl->next->name || !env->envl->next->value)
		perror_exit("Allocation error for env struct", free_env, env);
	env->envl->next->next = malloc(sizeof(t_envl));
	env->envl->next->next->name = ft_strdup("_");
	env->envl->next->next->value = ft_strdup("/usr/bin/env");
	env->envl->next->next->next = NULL;
	if (!env->envl->next->next->name || !env->envl->next->next->value)
		perror_exit("Allocation error for env struct", free_env, env);
	set_envp(env, 0, 0);
}

t_env	*init_env(char **envp)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		perror_exit("Allocation error for env struct", NULL, NULL);
	ft_bzero(env, sizeof(t_env));
	get_env(env, envp, -1);
	if (!env->envl)
		return (empty_env(env), env);
	set_env(env, env->envl);
	if (!env->path)
	{
		env->path = ft_strdup("");
		if (!env->path)
			perror_exit("Allocation error for PATH", free_env, env);
	}
	set_envp(env, 0, 0);
	if (!env->envp)
		perror_exit("Allocation error for env array", free_env, env);
	return (env);
}
