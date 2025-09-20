/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:51:28 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/20 07:52:39 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_st = 0;

int	main(int argc, char **argv, char **envp)
{
	t_sh	*sh;

	if (argc != 1)
		return (printf("Usage : %s\n", argv[0]), 1);
	sh = setup_minishell(envp);
	if (!sh)
		return (perror("Error malloc\n"), 1);
	loop(sh);
	return (free_all(sh), g_st);
}
