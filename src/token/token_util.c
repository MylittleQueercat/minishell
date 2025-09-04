/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:20:00 by hguo              #+#    #+#             */
/*   Updated: 2025/09/04 17:11:04 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_sep(char *str)
{
	if (!ft_strncmp(str, "&&", 2) || *str == ' ' || *str == '\t' || *str == '<'
		|| *str == '>' || *str == '|' || *str == '(' || *str == ')')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

void	skip_space(char **str)
{
	while (**str && isspace(**str))
		(*str)++;
}

int	skip_quote(char *line, size_t *i)
{
	char	quote;

	quote = line[*i];
	if (ft_strchr(line + *i + 1, quote))
	{
		(*i)++;
		while (line[*i] != quote)
			(*i)++;
		(*i)++;
		return (1);
	}
	return (0);
}

void	print_quote_err(t_minishell *sh, char c)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching '", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
	sh->exit_s = 258;
}
// when it fail in syntax, the return code is 258
