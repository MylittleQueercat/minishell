/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:58:32 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/02 19:16:34 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* main loop of the shell
 * Reads user input, processes commands, and executes them.
 * This function will be expanded to handle command parsing etc.
 */

int	loop(t_env *env)
{
	char	*prompt;
	char	*input;
	t_cmd	cmd;

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
		// For now, i just split the input and execute it directly
		// In the future, this will be replaced by a proper command parsing
		char **args = split_input(input);
		cmd.cmd = *args;
		cmd.args = args;
		cmd.argc = count_args(args);
		if (is_builtin_cmd(cmd.cmd))
		{
			if (exec_builtin(&cmd, env) == -1)
			{
				free_array(args);
				free(input);
				free(prompt);
				break ;
			}
		}
		else
			exec_external(&cmd, env);
		free_array(args);
		free(input);
		free(prompt);
	}
	return (0);
}
