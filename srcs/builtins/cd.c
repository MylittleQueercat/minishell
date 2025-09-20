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
		return (perror("getcwd"), 0);
	env->oldpwd = a_strdup(sh->sh_arena, get_env_value("PWD", env->envp));
	if (!env->oldpwd)
		return (printf("cd: allocation error\n"), 0);
	tmp = a_strjoin(sh->a, "OLDPWD=", env->oldpwd);
	if (!tmp)
		return (printf("cd: allocation error\n"), 0);
	change_env_var(sh, env, tmp);
	env->pwd = a_strdup(sh->sh_arena, cwd);
	if (!env->pwd)
		return (printf("cd: allocation error\n"), 0);
	free(cwd);
	tmp = a_strjoin(sh->a, "PWD=", env->pwd);
	if (!tmp)
		return (printf("cd: allocation error\n"), 0);
	change_env_var(sh, env, tmp);
	return (1);
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

void	ft_cd(t_sh *sh, t_cmd *cmd, t_env *env)
{
	if (cmd->argc > 2)
	{
		printf("cd: too many arguments\n");
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
		ft_pwd();
	}
	else if (chdir(cmd->args[1]) != 0)
	{
		perror("cd");
		g_st = 1;
	}
	else
		g_st = update_pwd(sh, env);
}
