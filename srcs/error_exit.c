/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 01:51:47 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/07 01:52:39 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_exit(const char *msg, void (*fn)(t_env *), t_env *arg)
{
	if (fn && arg)
		fn(arg);
	if (msg)
		perror(msg);
	exit(EXIT_FAILURE);
}

