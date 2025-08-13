/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:20:00 by hguo              #+#    #+#             */
/*   Updated: 2025/08/13 16:35:22 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell"

void	skip_space(char **line)
{
	while (**line && ft_isspace(**line))
		(*line)++;
}

int	is_sep(char *str)
{
	if (!ft_strncmp(str, "&&", 2) || *str == ' ' || *str == '\t' || *str == '<'
		|| *str == '>' || *str == '|' || *str == '(' || *str == ')')
		return (1);
	return (0);
}

void	skip_space(char **str)
{
	while (**str && isspace(**str))
		(*str)++;
}

int	skip_quote(char *str, size_t *i)
{
	char	quote;

	quote = str[*i];
	if (ft_strchr(line + *i + 1, quote))
	{
		(*i)++;
		while (str[*i] != quote)
			(*i)++;
		(*i)++;
		return (1);
	}
	return (0);
}

void	print_quote_err(char c)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching '");
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
	g_minishell.exit_s = 258;
}
// when it fail in syntax, the return code is 258
