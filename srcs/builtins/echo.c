/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:10:50 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/20 07:26:46 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	if (cmd->args[1] && ft_strncmp(cmd->args[1], "-n", 2) == 0)
		n_flag = 1;
	i = 1 + n_flag;
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	g_st = 0;
}
