/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_pre_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:29:39 by hguo              #+#    #+#             */
/*   Updated: 2025/09/20 06:58:54 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_squotes(t_minishell *sh, char *str, size_t *i)
{
	size_t	begin;

	begin = *i;
	(*i)++;
	while (str[*i] != '\'')
		(*i)++;
	(*i)++;
	return (a_substr(sh->a, str, begin, *i - begin));
}

char	*handle_dollar(t_minishell *sh, char *str, size_t *i)
{
	size_t	begin;
	char	*var;
	char	*env_val;

	(*i)++;
	if (ft_isdigit(str[*i]) || str[*i] == '@')
	{
		(*i)++;
		return (a_strdup(sh->a, ""));
	}
	else if (str[*i] == '?')
	{
		(*i)++;
		return (a_itoa(sh->a, g_st));
	}
	else if (!is_valid_var_char(str[*i]))
		return (a_strdup(sh->a, "$"));
	begin = *i;
	while (is_valid_var_char(str[*i]))
		(*i)++;
	var = a_substr(sh->a, str, begin, *i - begin);
	env_val = get_env_val(sh, var);
	if (!env_val)
		return (a_strdup(sh->a, ""));
	return (a_strdup(sh->a, env_val));
}

static char	*handle_dquote_str(t_minishell *sh, char *str, size_t *i)
{
	size_t	begin;

	begin = *i;
	while (str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (a_substr(sh->a, str, begin, *i - begin));
}

char	*handle_dquotes(t_minishell *sh, char *str, size_t *i)
{
	char	*arr;

	arr = a_strdup(sh->a, "\"");
	(*i)++;
	while (str[*i] != '"')
	{
		if (str[*i] == '$')
			arr = a_strjoin(sh->a, arr, handle_dollar(sh, str, i));
		else
			arr = a_strjoin(sh->a, arr, handle_dquote_str(sh, str, i));
	}
	(*i)++;
	return (a_strjoin(sh->a, arr, "\""));
}

char	*handle_normal(t_minishell *sh, char *str, size_t *i)
{
	size_t	begin;

	begin = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (a_substr(sh->a, str, begin, *i - begin));
}
