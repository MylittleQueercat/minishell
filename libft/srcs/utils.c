/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:47:29 by aprigent          #+#    #+#             */
/*   Updated: 2025/05/17 21:00:19 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printf_putstr(char *str, int len)
{
	int	i;

	i = -1;
	while (str[++i] && i < len)
		write(1, &str[i], 1);
	return (i);
}

int	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
	return (i);
}

int	write_padding(char c, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		write(1, &c, 1);
	return (i);
}

char	*ft_itoa_base(unsigned long nbr, char *base, char *str, int *i)
{
	if (nbr >= 16)
	{
		ft_itoa_base(nbr / 16, base, str, i);
		str[*i] = base[nbr % 16];
	}
	if (nbr < 16)
		str[*i] = base[nbr];
	(*i)++;
	return (str);
}
