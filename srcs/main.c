/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:51:28 by aprigent          #+#    #+#             */
/*   Updated: 2025/07/16 20:29:40 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Usage: ./minishell\n", 2);
		return (1);
	}
	if (!envp || !*envp)
	{
		ft_putstr_fd("Error: No environment variables provided.\n", 2);
		return (1);
	}
	env = init_env(envp);
	if (!env->envp)
	{
		ft_putstr_fd("Error: Failed to initialize environment.\n", 2);
		return (1);
	}
	loop(env);
	free_env(env);
	return (0);
}

