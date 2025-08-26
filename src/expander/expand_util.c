/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:17:02 by hguo              #+#    #+#             */
/*   Updated: 2025/08/21 19:23:53 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
