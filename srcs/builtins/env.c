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

void	ft_env(t_cmd *cmd, t_env *env)
{
	cmd->argc = count_args(cmd->args);
	if (cmd->argc > 1)
	{
		printf("env: '%s': No such file or directory\n", cmd->args[1]);
		g_st = 127;
	}
	else if (cmd->argc == 1)
	{
		print_sorted_env(env, 1);
		g_st = 0;
	}
}
