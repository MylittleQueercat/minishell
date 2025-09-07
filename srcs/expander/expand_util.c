/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:17:02 by hguo              #+#    #+#             */
/*   Updated: 2025/09/07 02:01:55 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var_char(char c)
{
	if (ft_isdigit(c) || ft_isalpha(c) || c == '_')
		return (1);
	return (0);
}

char	*get_env_val(t_minishell *sh, char *var)
{
	t_envl *envlst;

	envlst = sh->env->envl;
	while (envlst)
	{
		if (!ft_strncmp(var, envlst->name, ft_strlen(var) + 1))
			return (envlst->value);
		envlst = envlst->next;
	}
	return (NULL);
}

char	*clean_empty(char *str)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*tmp;
	char	*arr;

	if ((str[0] == '\'' && str[1] == '\'' && !str[2])
		|| (str[0] == '"' && str[1] == '"' && !str[2]))
		return (str);
	tmp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\'' && str[i + 1] == '\'')
			|| (str[i] == '"' && str[i + 1] == '"'))
			i += 2;
		else
			tmp[j++] = str[i++];
	}
	free(str);
	len = ft_strlen(tmp) + 1;
	arr = ft_calloc(len, sizeof(char));
	return (ft_strlcpy(arr, tmp, len), free(tmp), arr);
}
