/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 05:47:25 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/30 11:49:13 by hguo             ###   ########.fr       */
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
