/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:05:08 by aprigent          #+#    #+#             */
/*   Updated: 2025/05/29 21:05:10 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	clear(char *buff, int i)
{
	while (i <= BUFFER_SIZE)
		buff[i++] = 0;
	return (1);
}

int	nl_index(const char *str, int bytes)
{
	int	i;

	i = -1;
	if (!str)
		return (-1);
	while (str[++i])
	{
		if (str[i] == '\n')
			return (i + 1);
	}
	if (bytes < BUFFER_SIZE)
		return (bytes);
	return (-1);
}

char	*str_join(char *s1, const char *s2, int len)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (s1 && s1[i])
		i++;
	j = 0;
	while (j < len && s2[j])
		j++;
	str = malloc(i + j + 1);
	if (!str)
		return (free(s1), NULL);
	len = -1;
	while (++len < i)
		str[len] = s1[len];
	len = -1;
	while (++len < j)
		str[i + len] = s2[len];
	str[i + len] = 0;
	return (free(s1), str);
}
