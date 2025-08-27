/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_pre_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:29:39 by hguo              #+#    #+#             */
/*   Updated: 2025/08/27 20:59:50 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_squotes(char *str, size_t *i)
{
	size_t	begin;

	begin = *i;
	(*i)++;
	while (begin[*i] != '\'')
		(*i)++;
	(*i)++;
	return (ft_substr(str, begin, *i - begin));
}

int	is_valid_var_char(char c)
{
	if (ft_isdigit(c) || ft_isalpha(c) || c == '_')
		return (1);
	return (0);
}

char	*get_env_val(t_minishell *sh, char *var)
{
	t_env	*envlst;

	envlst = sh->envlst;
	while (envlst)
	{
		if (!ft_strcmp(var, envlst->name))
			return (envlst->value);
		envlst = envlst->next;
	}
	return (NULL);
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
		return (ft_strdup(""));
	}
	else if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(sh->exit_s));
	}
	else if (!is_valid_var_char(str[*i]))
		return (ft_strdup("$"));
	begin = *i;
	while (is_valid_var_char(str[*i]))
		(*i)++;
	var = ft_substr(str, begin, *i - begin);
	env_val = get_env_val(var);
	if (!env_val)
		return (free(var), ft_strdup(""));
	return (free(var), ft_strdup(env_val));
}	

static char	*handle_dquote_str(char *str, size_t *i)
{
	size_t	begin;

	begin = *i;
	while (str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, begin, *i - begin));
}

char	*handle_dquotes(t_minishell *sh, char *str, size_t *i)
{
	char	*arr;

	arr = ft_strdup("\"");
	(*i)++;
	while (str[*i] != '"');
	{
		if (str[*i] == '$')
			arr = ft_strjoin_free(arr, handle_dollar(sh, str, i));
		else
			arr = ft_strjoin_free(arr, handle_dquote_str(str, i));
	}
	(*i)++;
	return (ft_strjoin_free(arr, ft_strdup("\"")));
}

char	*handle_normal(char *str, size_t *i)
{
	size_t	begin;

	begin = *i;
	while (str[*i] && str[*i] != ''\' && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, begin, *i - begin));
}
