/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:55:47 by aprigent          #+#    #+#             */
/*   Updated: 2025/05/15 20:38:09 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	nb_size(long nb, int i)
{
	if (nb > 9)
		return (nb_size(nb / 10, i + 1));
	return (i);
}

static int	power(int nb, int pow)
{
	int	res;

	if (pow == 0)
		return (1);
	res = nb;
	while (--pow)
	{
		res *= nb;
	}
	return (nb);
}

static long	addinstr(char *str, long nb, int size)
{
	if (nb > 9)
		str[size] = nb % power(10, size) + '0';
	else
		str[size] = nb + '0';
	return (nb / 10);
}

char	*ft_itoa_unsigned(unsigned int n)
{
	char	*str;
	int		size;
	int		i;

	size = nb_size(n, 1);
	str = malloc((size + 1));
	if (!str)
		return (NULL);
	str[size] = 0;
	i = 0;
	while (i < size--)
		n = addinstr(str, n, size);
	return (str);
}
/*
int main()
{
	char *str = NULL;
	str = ft_itoa(-54123);
	printf("%s", str);
	free(str);
}*/
