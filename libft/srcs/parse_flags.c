/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:08:51 by aprigent          #+#    #+#             */
/*   Updated: 2025/05/17 21:01:59 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_struct(t_params *p)
{
	p->width = 0;
	p->precision = 0;
	p->zero = 0;
	p->minus = 0;
	p->hash = 0;
	p->plus = 0;
	p->space = 0;
	p->dot = 0;
	p->type = 0;
}

static void	parse_rest(const char **str, t_params *p)
{
	if (ft_isdigit(**str))
		p->width = printf_atoi(str);
	if (**str == '.')
	{
		p->dot += 1;
		(*str)++;
		p->precision = printf_atoi(str);
	}
	if (is_type(**str))
		p->type = **str;
}

t_params	parse_flags(const char **str)
{
	t_params	p;

	init_struct(&p);
	while (is_flag(**str))
	{
		if (**str == '#')
			p.hash += 1;
		if (**str == '0')
			p.zero += 1;
		if (**str == '-')
			p.minus += 1;
		if (**str == '+')
			p.plus += 1;
		if (**str == ' ')
			p.space += 1;
		(*str)++;
	}
	parse_rest(str, &p);
	if (p.dot)
		p.zero = 0;
	return (p);
}
