/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:16:13 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/02 19:13:38 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}

static int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	if (i == 0 || (i == 1 && (str[0] == '-' || str[0] == '+')))
		return (0);
	return (1);
}

int	ft_exit(t_minishell *sh, t_cmd *cmd, char *m)
{
	printf("exit\n");
	cmd->argc = count_args(cmd->args);
	if (cmd->argc > 2)
	{
		printf("%sexit: too many arguments\n", m);
		return (1);
	}
	if (cmd->argc == 2)
	{
		if (is_str_digit(cmd->args[1]) == 0)
		{
			printf("%sexit: %s: numeric argument required\n", m, cmd->args[1]);
			return (sh->exit_flag = 1, 2);
		}
		else
			return (sh->exit_flag = 1, ft_atoll(cmd->args[1]) % 256);
	}
	else
		return (sh->exit_flag = 1, 0);
}
