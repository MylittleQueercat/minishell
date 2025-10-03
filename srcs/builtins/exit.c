/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:16:13 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/30 12:33:57 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	count_args(char **args)
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

void	ft_exit(t_sh *sh, t_cmd *cmd)
{
	ft_putstr_fd("exit\n", 2);
	cmd->argc = count_args(cmd->args);
	if (cmd->argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_st = 1;
	}
	else if (cmd->argc == 2)
	{
		if (is_str_digit(cmd->args[1]) == 0)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit((free_all(sh), 2));
		}
		else
		{
			g_st = ft_atoll(cmd->args[1]) % 256;
			exit((free_all(sh), g_st));
		}
	}
	else
		exit((free_all(sh), g_st));
}
