/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_itoa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 06:55:58 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/20 06:56:30 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

static int	nb_size(long nb, int i)
{
	if (nb < 0)
		nb = -nb;
	if (nb > 9)
		return (nb_size(nb / 10, i + 1));
	return (i);
}

static long	addinstr(char *str, long nb, int size)
{
	if (nb > 9)
		str[size] = nb % 10 + '0';
	else
		str[size] = nb + '0';
	return (nb / 10);
}

char	*a_itoa(t_arena *arena, int n)
{
	char	*str;
	long	nb;
	int		size;
	int		i;

	nb = n;
	if (n < 0)
	{
		nb = -nb;
		size = nb_size(nb, 2);
	}
	else
		size = nb_size(nb, 1);
	str = arena_alloc(arena, size + 1);
	if (!str)
		return (NULL);
	str[size] = '\0';
	i = size - 1;
	while (i >= 0)
	{
		nb = addinstr(str, nb, i);
		i--;
	}
	return (str);
}
