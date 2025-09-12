/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:51:28 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/07 20:57:52 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*sh;
	int			exit;

	if (argc != 1)
		return (printf("Usage : %s\n", argv[0]), 1);
	sh = malloc(sizeof(t_minishell));
	if (!sh)
		return (printf("Error allocating memory for minishell\n"), 1);
	init_minishell(sh, envp);
	while (1)
	{
		run_iteration(sh);
		if (sh->tree)
			run_exec(sh);
		if (sh->exit_flag)
			break ;
		free(sh->line);
		sh->line = NULL;
		clear_ast(&sh->tree);
		clear_token_list(&sh->tokens);
	}
	exit = sh->exit_s;
	return (free_minishell(sh), exit);
}
