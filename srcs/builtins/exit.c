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

int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_cmd *cmd, t_env *env)
{
	char	*m;

	m = "minishell: ";
	printf("exit\n");
	if (cmd->argc > 2)
	{
		printf("%sexit: too many arguments\n", m);
		env->exit_status = 1;
		return (1);
	}
	if (cmd->argc == 2)
	{
		if (is_str_digit(cmd->args[1]) == 0)
		{
			printf("%sexit: %s: numeric argument required\n", m, cmd->args[1]);
			env->exit_status = 2;
			return (-1);
		}
		else
			env->exit_status = ft_atoll(cmd->args[1]) % 256;
	}
	else
		env->exit_status = 0;
	return (-1);
}
