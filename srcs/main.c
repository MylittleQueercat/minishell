/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:51:28 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/02 19:08:23 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	int		signal;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Usage: ./minishell\n", 2);
		return (1);
	}
	env = init_env(envp);
	if (!env->envp)
	{
		ft_putstr_fd("Error: Failed to initialize environment.\n", 2);
		return (1);
	}
	env->exit_status = -1;
	add_colors(env);
	loop(env);
	signal = env->exit_status;
	free_env(env);
	return (signal);
}
