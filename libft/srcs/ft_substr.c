/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:28:55 by aprigent          #+#    #+#             */
/*   Updated: 2025/04/29 11:07:37 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	size;
	size_t	len_s;

	size = 0;
	len_s = ft_strlen(s);
	if (!s)
		return (NULL);
	while ((size_t)start + size < len_s && size < len)
		size++;
	sub = malloc(size + 1);
	if (!sub)
		return (NULL);
	sub[size] = 0;
	while (size--)
		sub[size] = s[start + size];
	return (sub);
}
