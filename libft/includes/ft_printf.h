/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:55:45 by aprigent          #+#    #+#             */
/*   Updated: 2025/05/18 22:19:17 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include "libft.h"

typedef struct s_params
{
	int		width;
	int		precision;
	int		zero;
	int		minus;
	int		hash;
	int		plus;
	int		space;
	int		dot;
	char	type;
}			t_params;

int			ft_printf(const	char *str, ...);

int			write_padding(char c, int len);
int			is_flag(char c);
int			is_type(char c);

t_params	parse_flags(const char **str);
int			params_handler(t_params *p, va_list args);

int			print_char(t_params *p, char c);
int			print_str(t_params *p, char *str);
int			print_pointer(t_params *p, void *ptr);
int			print_int(t_params *p, int n);
int			print_unsigned(t_params *p, unsigned int u);
int			print_hex(t_params *p, unsigned int x);

int			printf_atoi(const char **str);
int			ft_putstr(char *str);
int			printf_putstr(char *str, int len);
char		*ft_itoa_base(unsigned long nbr, char *base, char *str, int *i);
char		*ft_itoa_unsigned(unsigned int n);

#endif
