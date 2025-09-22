/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:12:21 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/20 07:48:56 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	*a_realloc(t_arena *arena, void *ptr, size_t old_size, size_t size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (arena_alloc(arena, size));
	new_ptr = arena_alloc(arena, size);
	if (old_size < size)
		size = old_size;
	if (new_ptr)
	{
		ft_memcpy(new_ptr, ptr, size);
		return (new_ptr);
	}
	return (NULL);
}

void	arena_init(t_arena *arena, size_t size)
{
	if (arena == NULL)
		return ;
	arena->size = size;
	arena->used = 0;
	arena->data = malloc(size);
	if (arena->data == NULL)
	{
		arena->size = 0;
		return ;
	}
	arena->next = NULL;
}

void	arena_free(t_arena *arena)
{
	t_arena	*next;

	if (arena == NULL)
		return ;
	next = arena->next;
	ft_bzero(arena->data, arena->size);
	free(arena->data);
	free(arena);
	if (next != NULL)
		arena_free(next);
}

void	*arena_alloc(t_arena *arena, size_t size)
{
	void	*ptr;

	if (arena->used + size > arena->size)
	{
		if (arena->next == NULL)
		{
			arena->next = malloc(sizeof(t_arena));
			if (arena->next == NULL)
				return (NULL);
			arena_init(arena->next, arena->size + size);
			if (arena->next->data == NULL)
			{
				free(arena->next);
				arena->next = NULL;
				return (NULL);
			}
		}
		return (arena_alloc(arena->next, size));
	}
	ptr = (char *)arena->data + arena->used;
	arena->used += size;
	return (ptr);
}
