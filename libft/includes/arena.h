/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:34:47 by aprigent          #+#    #+#             */
/*   Updated: 2025/07/07 16:30:15 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

# include "libft.h"

typedef struct s_block
{
	size_t			size;
}	t_block;

typedef struct s_arena
{
	size_t		size;
	size_t		used;
	void		*data;
	struct s_arena		*next;
}	t_arena;

void	arena_init(t_arena *arena, size_t size);
void	*arena_alloc(t_arena *arena, size_t size);
void	*arena_realloc(t_arena *arena, void *ptr, size_t old_size, size_t size);
void	arena_free(t_arena *arena);

typedef struct s_split
{
	const char	*s;
	char		c;
}	t_split;

char	**arena_split(t_arena *arena, const char *str, char c);

#endif // ARENA_H
