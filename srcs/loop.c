/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:58:32 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/07 01:55:53 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* main loop of the shell
 * Reads user input, processes commands, and executes them.
 * This function will be expanded to handle command parsing etc.
 */

void	loop(t_env *env)
{
	char	*prompt;
	char	*input;

	while (1)
	{
		prompt = build_prompt(env->pwd);
		if (!prompt)
		{
			ft_putstr_fd("Error: Failed to create prompt.\n", 2);
			break ;
		}
		input = readline(prompt);
		if (!input)
		{ // If readline returns NULL, it means EOF (Ctrl+D)
			printf("\n");
			break ;
		}
		if (input[0] == '\0')
		{ // If the input is empty, we just continue to the next iteration
			free(input);
			continue ;
		}
		free(input);
		free(prompt);
	}
}
