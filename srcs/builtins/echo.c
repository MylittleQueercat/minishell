/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:10:50 by aprigent          #+#    #+#             */
/*   Updated: 2025/07/17 12:15:15 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	if (cmd->args[1] && ft_strncmp(cmd->args[1], "-n", 2) == 0)
		n_flag = 1;
	i = 1 + n_flag;
	while (cmd->args[i])
	{
		//Must add handling of $, need parsing;
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
