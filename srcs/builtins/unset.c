/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:50:17 by aprigent          #+#    #+#             */
/*   Updated: 2025/07/18 12:07:45 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_cmd *cmd, t_env *env)
{
	t_envl	*current;
	t_envl	*prev;
	int		i;

	if (!cmd->args[1])
		return (0);
	i = 1;
	while (cmd->args[i])
	{
		if (is_valid_identifier(cmd->args[i]) == 0)
		{
			printf("unset: '%s': not a valid identifier\n", cmd->args[i]);
			return (1);
		}
		current = env->envl;
		prev = NULL;
		while (current)
		{
			if (ft_strcmp(current->name, cmd->args[i]) == 0)
			{
				if (prev)
					prev->next = current->next;
				else
					env->envl = current->next;
				free(current->name);
				free(current->value);
				free(current);
				break ;
			}
			prev = current;
			current = current->next;
		}
		i++;
	}
	return (update_envp(env));
}
