/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:39:10 by aprigent          #+#    #+#             */
/*   Updated: 2025/07/07 16:37:28 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include "ft_printf.h"

static size_t	split_strlen(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	count_words(const char *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			words++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (words);
}

int	malloc_split(t_arena *arena, char **arr, t_split *d, int i)
{
	int	j;

	j = 0;
	arr[i] = arena_alloc(arena, (split_strlen(d->s, d->c) + 1) * sizeof(char));
	if (!arr[i])
		return (1);
	while (!(*d->s == d->c) && *d->s)
		arr[i][j++] = *d->s++;
	arr[i][j] = 0;
	return (0);
}

char	**arena_split(t_arena *arena, const char *s, char c)
{
	int		i;
	int		len;
	char	**arr;
	t_split	d;

	i = 0;
	d.s = s;
	d.c = c;
	len = count_words(s, c);
	arr = arena_alloc(arena, (len + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (i < len)
	{
		while (*s == c)
			s++;
		d.s = s;
		if (malloc_split(arena, arr, &d, i))
			return (NULL);
		while (*s && *s != c)
			s++;
		i++;
	}
	arr[i] = 0;
	return (arr);
}
