/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:20:53 by aprigent          #+#    #+#             */
/*   Updated: 2025/05/17 21:27:38 by aprigent         ###   ########.fr       */
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

int	print_unsigned(t_params *p, unsigned int u)
{
	char	*str;
	int		count;
	int		len;
	int		pad;

	str = ft_itoa_unsigned(u);
	if (!str)
		return (-1);
	len = ft_strlen(str);
	count = print_pad(p, len);
	if (u || !(p->dot && !p->precision))
		count += write(1, str, len);
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
