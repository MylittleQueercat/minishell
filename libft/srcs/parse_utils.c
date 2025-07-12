/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:40:34 by aprigent          #+#    #+#             */
/*   Updated: 2025/05/14 23:34:36 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printf_atoi(const char **str)
{
	int	result;

	result = 0;
	while (ft_isdigit(**str))
	{
		result = result * 10 + (**str - '0');
		(*str)++;
	}
	return (result);
}

int	is_flag(char c)
{
	char	*flags;

	flags = "#0-+ ";
	while (*flags)
	{
		if (*flags == c)
			return (1);
		flags++;
	}
	return (0);
}

int	is_type(char c)
{
	char	*types;

	types = "cspdiuxX%";
	while (*types)
	{
		if (*types == c)
			return (1);
		types++;
	}
	return (0);
}
