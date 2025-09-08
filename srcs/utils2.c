/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 19:49:12 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/04 19:49:27 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_perror(t_env *env, const char *msg)
{
	if (env)
		free_env(env);
	perror(msg);
	exit(EXIT_FAILURE);
}
