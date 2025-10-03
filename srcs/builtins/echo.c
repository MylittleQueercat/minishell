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

static int	check_n(char *str, int *n_flag)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (*n_flag = 1, 1);
	}
	return (0);
}

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	cmd->argc = count_args(cmd->args);
	i = 0;
	if (cmd->argc > 1)
	{
		while (cmd->args[++i] && ft_strncmp(cmd->args[i], "-n", 2) == 0)
			if (check_n(cmd->args[i], &n_flag) == 0)
				break ;
	}
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
