/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:23:30 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/20 08:08:18 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_pwd(t_sh *sh, t_env *env)
{
	char	*cwd;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("getcwd"), 1);
	tmp = get_env_value("PWD", env->envp);
	if (!tmp)
		tmp = a_strdup(sh->sh_arena, "");
	env->oldpwd = a_strdup(sh->sh_arena, tmp);
	if (!env->oldpwd)
		exit((free(cwd), perror("malloc"), free_all(sh), 1));
	tmp = a_strjoin(sh->a, "OLDPWD=", env->oldpwd);
	if (!tmp)
		exit((free(cwd), perror("malloc"), free_all(sh), 1));
	change_var(sh, env, tmp);
	env->pwd = a_strdup(sh->sh_arena, cwd);
	if (!env->pwd)
		exit((free(cwd), perror("malloc"), free_all(sh), 1));
	free(cwd);
	tmp = a_strjoin(sh->a, "PWD=", env->pwd);
	if (!tmp)
		exit((perror("malloc"), free_all(sh), 1));
	change_var(sh, env, tmp);
	return (update_envp(sh, env, 0, 0), 0);
}

void	cd_no_arg(t_sh *sh, t_env *env)
{
	char	*home;

	home = get_env_value("HOME", env->envp);
	if (!home)
	{
		printf("cd: HOME not set\n");
		g_st = 1;
	}
	else if (chdir(home) != 0)
	{
		perror("cd");
		g_st = 1;
	}
	else
		g_st = update_pwd(sh, env);
}

void	cd_root(t_sh *sh, t_env *env)
{
	if (chdir("/") != 0)
	{
		perror("cd");
		g_st = 1;
	}
	else
		g_st = update_pwd(sh, env);
}

void	cd_oldpwd(t_sh *sh, t_env *env)
{
	char	*oldpwd;

	oldpwd = get_env_value("OLDPWD", env->envp);
	if (!oldpwd)
	{
		printf("cd: OLDPWD not set\n");
		g_st = 1;
	}
	else if (chdir(oldpwd) != 0)
	{
		perror("cd");
		g_st = 1;
	}
	else
	{
		g_st = update_pwd(sh, env);
		if (g_st == 0)
			printf("%s\n", env->pwd);
	}
}

void	ft_cd(t_sh *sh, t_cmd *cmd, t_env *env)
{
	if (cmd->argc > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		g_st = 1;
	}
	else if (cmd->argc == 1 || ft_strncmp(cmd->args[1], "~", 2) == 0
		|| ft_strncmp(cmd->args[1], "--", 2) == 0
		|| ft_strncmp(cmd->args[1], "$HOME", 6) == 0
		|| ft_strncmp(cmd->args[1], "~/", 2) == 0)
		cd_no_arg(sh, env);
	else if (ft_strncmp(cmd->args[1], "-", 2) == 0)
	{
		cmd->args[1] = NULL;
		cd_oldpwd(sh, env);
	}
	else if (chdir(cmd->args[1]) != 0)
		return (perror("cd"), (void)(g_st = 1));
	else
		g_st = update_pwd(sh, env);
}
