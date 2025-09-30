/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:02:48 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/30 11:52:12 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env(t_sh *sh, t_env *env, char **envp, int i)
{
	t_envl	*new;
	int		equal_pos;

	while (envp[++i])
	{
		new = (t_envl *)arena_alloc(sh->sh_arena, sizeof(t_envl));
		if (!new)
			exit((perror("Allocation error for env struct"), free_all(sh), 1));
		if (!env->envl)
			env->envl = new;
		else
			get_last_envl(env->envl)->next = new;
		equal_pos = ft_strchr(envp[i], '=') - envp[i];
		if (equal_pos == -1)
			continue ;
		new->name = (char *)arena_alloc(sh->sh_arena, equal_pos + 2);
		if (!new->name)
			exit((perror("Allocation error for env name"), free_all(sh), 1));
		ft_strlcpy(new->name, envp[i], equal_pos + 1);
		new->name[equal_pos] = 0;
		new->value = a_strdup(sh->sh_arena, envp[i] + equal_pos + 1);
		if (!new->value)
			exit((perror("Allocation error for env value"), free_all(sh), 1));
		new->next = NULL;
	}
}

void	set_env(t_sh *sh, t_env *env, t_envl *curr)
{
	while (curr)
	{
		if (ft_strcmp(curr->name, "PATH") == 0)
		{
			env->path = a_strdup(sh->sh_arena, curr->value);
			if (!env->path)
				exit((perror("Allocation error for PATH"), free_all(sh), 1));
		}
		else if (ft_strcmp(curr->name, "PWD") == 0)
		{
			env->pwd = a_strdup(sh->sh_arena, curr->value);
			if (!env->pwd)
				exit((perror("Allocation error for PWD"), free_all(sh), 1));
		}
		else if (ft_strcmp(curr->name, "OLDPWD") == 0)
		{
			env->oldpwd = a_strdup(sh->sh_arena, curr->value);
			if (!env->oldpwd)
				exit((perror("Allocation error for OLDPWD"), free_all(sh), 1));
		}
		curr = curr->next;
	}
}

void	set_envp(t_sh *sh, t_env *env, int i, int size)
{
	t_envl	*curr;

	curr = env->envl;
	while (curr && ++size)
		curr = curr->next;
	env->envp = arena_alloc(sh->sh_arena, sizeof(char *) * (size + 1));
	if (!env->envp)
		return ;
	curr = env->envl;
	while (curr)
	{
		if (curr->value)
		{
			env->envp[i] = a_strjoin(sh->sh_arena, curr->name, "=");
			env->envp[i] = a_strjoin(sh->sh_arena, env->envp[i], curr->value);
		}
		else
			env->envp[i] = a_strdup(sh->sh_arena, curr->name);
		if (!env->envp[i])
			exit((perror("Allocation error for env array"), free_all(sh), 1));
		i++;
		curr = curr->next;
	}
	env->envp[i] = NULL;
}

void	empty_env(t_sh *sh, t_env *env)
{
	env->pwd = getcwd(NULL, 0);
	env->path = a_strdup(sh->sh_arena, "");
	if (!env->pwd || !env->path)
		exit((perror("Allocation error for env struct"), free_all(sh), 1));
	env->envl = arena_alloc(sh->sh_arena, sizeof(t_envl));
	if (!env->envl)
		exit((perror("Allocation error for env struct"), free_all(sh), 1));
	env->envl->name = a_strdup(sh->sh_arena, "PWD");
	env->envl->value = a_strdup(sh->sh_arena, env->pwd);
	env->envl->next = arena_alloc(sh->sh_arena, sizeof(t_envl));
	if (!env->envl->next || !env->envl->name || !env->envl->value)
		exit((perror("Allocation error for env struct"), free_all(sh), 1));
	env->envl->next->name = a_strdup(sh->sh_arena, "SHLVL");
	env->envl->next->value = a_strdup(sh->sh_arena, "1");
	env->envl->next->next = arena_alloc(sh->sh_arena, sizeof(t_envl));
	if (!env->envl->next->name || !env->envl->next->value
		|| !env->envl->next->next)
		exit((perror("Allocation error for env struct"), free_all(sh), 1));
	env->envl->next->next->name = a_strdup(sh->sh_arena, "_");
	env->envl->next->next->value = a_strdup(sh->sh_arena, "/usr/bin/env");
	env->envl->next->next->next = NULL;
	if (!env->envl->next->next->name || !env->envl->next->next->value)
		exit((perror("Allocation error for env struct"), free_all(sh), 1));
	set_envp(sh, env, 0, 0);
}

t_env	*init_env(t_sh *sh, char **envp)
{
	t_env	*env;

	env = (t_env *)arena_alloc(sh->sh_arena, sizeof(t_env));
	if (!env)
		exit((perror("Allocation error for env struct"), free_all(sh), 1));
	ft_bzero(env, sizeof(t_env));
	get_env(sh, env, envp, -1);
	if (!env->envl)
		return (empty_env(sh, env), env);
	set_env(sh, env, env->envl);
	if (!env->path)
	{
		env->path = a_strdup(sh->sh_arena, "");
		if (!env->path)
			exit((perror("Allocation error for PATH"), free_all(sh), 1));
	}
	set_envp(sh, env, 0, 0);
	if (!env->envp)
		exit((perror("Allocation error for env array"), free_all(sh), 1));
	return (env);
}
