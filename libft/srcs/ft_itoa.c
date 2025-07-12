/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:55:47 by aprigent          #+#    #+#             */
/*   Updated: 2025/05/15 19:55:14 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nb_size(long nb, int i)
{
	if (nb < 0)
		nb = -nb;
	if (nb > 9)
		return (nb_size(nb / 10, i + 1));
	return (i);
}

int	power(int nb, int pow)
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

long	addinstr(char *str, long nb, int size)
{
	if (nb > 9)
		str[size] = nb % power(10, size) + '0';
	else
		str[size] = nb + '0';
	return (nb / 10);
}

char	*ft_itoa(int n)
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
	str = malloc((size + 1));
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	str[size] = 0;
	i = 0;
	if (n < 0)
		i = 1;
	while (i < size--)
		nb = addinstr(str, nb, size);
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
