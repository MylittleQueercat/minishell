/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:41:09 by aprigent          #+#    #+#             */
/*   Updated: 2025/05/17 21:14:10 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_pad(t_params *p, int len)
{
	int	count;
	int	zero_pad;

	count = 0;
	zero_pad = p->precision - len;
	if (zero_pad < 0)
		zero_pad = 0 ;
	if (!p->minus && !p->zero)
		count += write_padding(' ', p->width - len - zero_pad);
	if (p->dot)
		count += write_padding('0', zero_pad);
	else if (p->zero)
		count += write_padding('0', p->width - len);
	return (count);
}

static int	hash(t_params *p, unsigned int x, int *len)
{
	int	count;

	count = 0;
	if (p->hash && x && p->type == 'x')
		count = write(1, "0x", 2);
	if (p->hash && x && p->type == 'X')
		count = write(1, "0X", 2);
	if (p->hash && x)
		len -= 2;
	return (count);
}

static char	*base(t_params *p, unsigned int x, int *len)
{
	if (p->type == 'x')
		return (ft_itoa_base(x, "0123456789abcdef", malloc(100), len));
	else
		return (ft_itoa_base(x, "0123456789ABCDEF", malloc(100), len));
}

int	print_hex(t_params *p, unsigned int x)
{
	char	*str;
	int		count;
	int		len;
	int		pad;

	len = 0;
	str = base(p, x, &len);
	if (!str)
		return (-1);
	str[len] = 0;
	count = hash(p, x, &len);
	count += print_pad(p, len);
	if (x || !(p->dot && !p->precision))
		count += write(1, str, ft_strlen(str));
	else if (p->width && p->dot && !p->precision)
		count += write_padding(' ', 1);
	if (p->minus && p->width > len)
	{
		pad = p->precision - len;
		if (pad < 0)
			pad = 0;
		count += write_padding(' ', p->width - len - pad);
	}
	free(str);
	return (count);
}
