/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 05:47:25 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/20 05:48:15 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arena	*setup_arena(void)
{
	t_arena	*a;

	a = malloc(sizeof(t_arena));
	if (!a)
		return (printf("Error malloc\n"), NULL);
	arena_init(a, 1024 * 1024);
	if (a->data == NULL)
		return (printf("Error malloc\n"), free(a), NULL);
	return (a);
}

