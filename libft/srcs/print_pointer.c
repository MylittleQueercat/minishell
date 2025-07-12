/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:46:44 by aprigent          #+#    #+#             */
/*   Updated: 2025/05/17 21:07:14 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_nil(t_params *p)
{
	char	*str;
	int		count;

	str = "(nil)";
	count = 0;
	if (!p->minus)
		count += write_padding(' ', p->width - 5);
	count += write(1, str, 5);
	if (p->minus)
		count += write_padding(' ', p->width - 5);
	return (count);
}

int	print_pointer(t_params *p, void *ptr)
{
	char	*str;
	int		count;
	int		len;
	int		pad;

	if (!ptr)
		return (print_nil(p));
	len = 0;
	str = "0123456789abcdef";
	str = ft_itoa_base((unsigned long)ptr, str, malloc(100), &len);
	str[len] = 0;
	count = 0;
	len = ft_strlen(str);
	pad = 2 + len;
	if (!p->minus)
		count += write_padding(' ', p->width - pad);
	count += write(1, "0x", 2);
	count += write(1, str, len);
	if (p->minus)
		count += write_padding(' ', p->width - pad);
	free(str);
	return (count);
}
