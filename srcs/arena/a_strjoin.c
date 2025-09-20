/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_strjoin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 06:04:40 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/20 06:05:11 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

char	*a_strjoin(t_arena *arena, const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined = arena_alloc(arena, len1 + len2 + 1);
	if (!joined)
		return (NULL);
	ft_memcpy(joined, s1, len1);
	ft_memcpy(joined + len1, s2, len2);
	joined[len1 + len2] = 0;
	return (joined);
}
