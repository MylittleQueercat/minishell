/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:20:17 by aprigent          #+#    #+#             */
/*   Updated: 2025/07/17 12:52:30 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(const char *var, char **envp)
{
	int		i;
	char	*equal_sign;
	size_t	var_len;

	if (!var || !envp)
		return (NULL);
	var_len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign && (size_t)(equal_sign - envp[i]) == var_len
			&& ft_strncmp(envp[i], var, var_len) == 0)
			return (equal_sign + 1);
		i++;
	}
	return (NULL);
}

int	ft_env(t_cmd *cmd, t_env *env)
{
	int	i;

	if (cmd->args[1])
	{
		printf("env: '%s': No such file or directory\n", cmd->args[1]);
		return (1);
	}
	i = 0;
	while (env->envp[i])
		printf("%s\n", env->envp[i++]);
	return (0);
}
