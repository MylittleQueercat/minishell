/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:23:30 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/02 23:02:01 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_pwd(t_env *env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return (0);
	}
	if (env->oldpwd)
		free(env->oldpwd);
	env->oldpwd = ft_strdup(get_env_value("PWD", env->envp));
	update_env_value("OLDPWD", env->oldpwd, env);
	if (env->pwd)
		free(env->pwd);
	env->pwd = cwd;
	update_env_value("PWD", env->pwd, env);
	return (1);
}

int	cd_no_arg(t_env *env)
{
	char	*home;

	home = get_env_value("HOME", env->envp);
	if (!home)
	{
		printf("cd: HOME not set\n");
		return (0);
	}
	if (chdir(home) != 0)
	{
		perror("cd");
		return (0);
	}
	return (update_pwd(env));
}

int	cd_root(t_env *env)
{
	if (chdir("/") != 0)
	{
		perror("cd");
		return (0);
	}
	return (update_pwd(env));
}

int	ft_cd(t_cmd *cmd, t_env *env)
{
	if (cmd->argc > 2)
	{
		printf("cd: too many arguments\n");
		return (0);
	}
	if (cmd->argc == 1 || ft_strncmp(cmd->args[1], "~", 2) == 0
		|| ft_strncmp(cmd->args[1], "--", 2) == 0
		|| ft_strncmp(cmd->args[1], "$HOME", 6) == 0
		|| ft_strncmp(cmd->args[1], "~/", 2) == 0)
		return (cd_no_arg(env));
	if (ft_strncmp(cmd->args[1], "-", 2) == 0)
	{
		cmd->args[1] = NULL;
		return (ft_pwd(cmd));
	}
	if (chdir(cmd->args[1]) != 0)
	{
		perror("cd");
		return (0);
	}
	return (update_pwd(env));
}
