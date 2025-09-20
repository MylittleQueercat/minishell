/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 05:37:39 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/20 08:11:51 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

# include <stdlib.h>
# include <stdbool.h>
# include <stddef.h>
# include "libft.h"

typedef struct s_arena
{
	size_t		size;
	size_t		used;
	void		*data;
	struct s_arena		*next;
}	t_arena;


void	arena_init(t_arena *arena, size_t size);
void	*arena_alloc(t_arena *arena, size_t size);
void	*a_realloc(t_arena *arena, void *ptr, size_t old_size, size_t size);
void	arena_free(t_arena *arena);
char	*a_strjoin(t_arena *arena, const char *s1, const char *s2);
char	*a_strdup(t_arena *arena, const char *s);
char	**a_split(t_arena *arena, const char *str, char c);
char	*a_itoa(t_arena *arena, int n);
char	*a_substr(t_arena *arena, const char *s, unsigned int start, size_t len);
void	*a_calloc(t_arena *arena, size_t count, size_t size);

typedef struct s_split
{
	const char	*s;
	char		c;
}	t_split;

#endif // ARENA_H
