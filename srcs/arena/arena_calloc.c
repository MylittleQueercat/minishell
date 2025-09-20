/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_calloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:58:37 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/20 08:12:06 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	*a_calloc(t_arena *arena, size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = arena_alloc(arena, nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, (nmemb * size));
	return (ptr);
}
