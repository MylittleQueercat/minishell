/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_substr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 06:24:38 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/20 06:24:43 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

char	*a_substr(t_arena *arena, const char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*sub;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (a_strdup(arena, ""));
	if (len > s_len - start)
		len = s_len - start;
	sub = arena_alloc(arena, len + 1);
	if (!sub)
		return (NULL);
	ft_memcpy(sub, s + start, len);
	sub[len] = '\0';
	return (sub);
}
