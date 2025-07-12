/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:30:44 by aprigent          #+#    #+#             */
/*   Updated: 2025/05/17 21:06:03 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*flags(t_params *p)
{
	if (p->precision < 6 && p->precision)
		return ("");
	return ("(null)");
}

int	print_str(t_params *p, char *s)
{
	int	count;
	int	len;

	if (!s)
		s = flags(p);
	count = 0;
	len = ft_strlen(s);
	if (p->precision && p->precision < len)
		len = p->precision;
	if (p->dot && !p->precision)
		len = 0;
	if (!p->minus)
		count += write_padding(' ', p->width - len);
	if (p->dot)
		count += printf_putstr(s, p->precision);
	else
		count += ft_putstr(s);
	if (p->minus)
		count += write_padding(' ', p->width - len);
	return (count);
}
