/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:50:17 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/30 11:43:35 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env_var(t_env *env, char *var)
{
	t_envl	*current;
	t_envl	*prev;

	current = env->envl;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->name, var) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				env->envl = current->next;
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_unset(t_sh *sh, t_cmd *cmd, t_env *env)
{
	int		i;

	if (!cmd->args[1])
		return (g_st = 0, (void)0);
	i = 1;
	while (cmd->args[i])
	{
		if (is_valid_identifier(cmd->args[i]) == 0)
		{
			printf("unset: '%s': not a valid identifier\n", cmd->args[i]);
			return (g_st = 1, (void)0);
		}
		remove_env_var(env, cmd->args[i]);
		i++;
	}
	g_st = update_envp(sh, env);
}
