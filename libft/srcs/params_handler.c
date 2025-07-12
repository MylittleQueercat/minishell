/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:01:38 by aprigent          #+#    #+#             */
/*   Updated: 2025/05/17 21:27:19 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	params_handler(t_params *p, va_list args)
{
	if (p->type == 'c')
		return (print_char(p, va_arg(args, int)));
	else if (p->type == 's')
		return (print_str(p, va_arg(args, char *)));
	else if (p->type == 'p')
		return (print_pointer(p, va_arg(args, void *)));
	else if (p->type == 'd' || p->type == 'i')
		return (print_int(p, va_arg(args, int)));
	else if (p->type == 'u')
		return (print_unsigned(p, va_arg(args, unsigned int)));
	else if (p->type == 'x' || p->type == 'X')
		return (print_hex(p, va_arg(args, unsigned int)));
	else if (p->type == '%')
		return (write(1, "%", 1));
	return (0);
}
