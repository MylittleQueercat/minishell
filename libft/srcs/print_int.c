/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:40:24 by aprigent          #+#    #+#             */
/*   Updated: 2025/05/17 21:27:05 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_sign(t_params *p, int minus)
{
	if (minus)
		return (write(1, "-", 1));
	else if (p->plus)
		return (write(1, "+", 1));
	else if (p->space)
		return (write(1, " ", 1));
	return (0);
}

static int	print_pad(t_params *p, int len, int minus)
{
	int	count;
	int	zero_pad;
	int	sign;

	count = 0;
	sign = (minus || p->plus || p->space);
	if ((p->minus || p->width <= len) && !p->zero && p->precision <= len)
		count += print_sign(p, minus);
	zero_pad = p->precision - (len - sign);
	if (zero_pad < 0)
		zero_pad = 0 ;
	if (!p->minus && !p->zero)
		count += write_padding(' ', p->width - len - zero_pad);
	if (!((p->minus || p->width <= len) && !p->zero && p->precision <= len))
		count += print_sign(p, minus);
	if (p->dot)
		count += write_padding('0', zero_pad);
	else if (p->zero)
		count += write_padding('0', p->width - len);
	return (count);
}

int	print_int(t_params *p, int n)
{
	char	*str;
	int		count;
	int		len;
	int		pad;

	str = ft_itoa(n);
	if (!str)
		return (-1);
	len = ft_strlen(str);
	pad = len;
	if (p->precision < len && p->precision)
		pad = p->precision;
	count = print_pad(p, len, (n < 0));
	if (n || !(p->dot && !p->precision))
		count += write(1, str + (n < 0), ft_strlen(str + (n < 0)));
	else if (p->width && p->dot && !p->precision)
		count += write_padding(' ', 1);
	if (p->minus && p->width > len)
	{
		pad = p->precision - (len - (((n < 0) || p->plus || p->space)));
		if (pad < 0)
			pad = 0;
		count += write_padding(' ', p->width - len - pad);
	}
	return (free(str), count);
}
