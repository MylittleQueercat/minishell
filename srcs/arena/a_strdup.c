/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_strdup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 06:03:50 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/20 06:04:11 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

char	*a_strdup(t_arena *arena, const char *s)
{
	size_t	len;
	char	*dup;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = arena_alloc(arena, len + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}
