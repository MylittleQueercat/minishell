/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:47:38 by aprigent          #+#    #+#             */
/*   Updated: 2025/04/29 10:58:03 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	size_t			i;

	ptr1 = (unsigned char *)dest;
	ptr2 = (unsigned char *)src;
	if (!ptr1 && !ptr2)
		return (ptr1);
	i = -1;
	if (ptr1 > ptr2)
	{
		while (len--)
			ptr1[len] = ptr2[len];
	}
	else
	{
		while (++i < len)
			ptr1[i] = ptr2[i];
	}
	return (ptr1);
}
/*
int main()
{
	char *dest = malloc(10);
	const char *src = "adawdawd";
	size_t n = 4;
	printf("%s", (char *)ft_memmove(dest, src, n));
}*/
