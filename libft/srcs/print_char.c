/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:21:51 by aprigent          #+#    #+#             */
/*   Updated: 2025/05/17 21:08:59 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(t_params *p, char c)
{
	int	count;

	count = 0;
	if (!p->minus)
	{
		count += write_padding(' ', p->width - 1);
		count += write(1, &c, 1);
	}
	else
	{
		count += write(1, &c, 1);
		count += write_padding(' ', p->width - 1);
	}
	return (count);
}
