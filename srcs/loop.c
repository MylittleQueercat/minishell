/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:58:32 by aprigent          #+#    #+#             */
/*   Updated: 2025/07/16 20:29:25 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* main loop of the shell
 * Reads user input, processes commands, and executes them.
 * This function will be expanded to handle command parsing etc.
 */

void	loop(t_env *env)
{
	char	*input;
	t_cmd	cmd;

	while (1)
	{
		input = readline("minishell> ");
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
		// For now, i just split the input and execute it directly
		// In the future, this will be replaced by a proper command parsing
		char **args = split_input(input);
		cmd.cmd = *args;
		cmd.args = args;
		cmd.type = CMD_EXTERNAL; // For now, we assume it's an external command
		exec_cmd(&cmd, env);
		free_array(args);
		free(input);
	}
}
