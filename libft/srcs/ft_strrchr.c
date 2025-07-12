/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:32:08 by aprigent          #+#    #+#             */
/*   Updated: 2025/04/29 12:27:16 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;

	str = (char *)s + ft_strlen(s);
	while (*str != (char)c)
	{
		if (str == (char *)s)
			return (NULL);
		str--;
	}
	return (str);
}
/*
int main()
{
	char *s = "tripouille";
	//char *str = "teste";
	//printf("%p | %p\n", ft_strrchr(str, 'e'), str);
	printf("%s\n", ft_strrchr(s, 't' + 256));
}*/
