/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:08:38 by aprigent          #+#    #+#             */
/*   Updated: 2025/04/29 11:11:37 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	ptr = (char *)big;
	if (little == big || !*little)
		return (ptr);
	i = -1;
	while (*ptr && ++i < len)
	{
		if (*ptr == little[0])
		{
			j = -1;
			while (little[++j] && ptr[j])
			{
				if (ptr[j] != little[j])
					break ;
			}
			if (!little[j] && j + i <= len)
				return (ptr);
		}
		ptr++;
	}
	return (NULL);
}
/*
int main()
{
	printf("%s\n", ft_strnstr("aaxx", "xx", 4));
}*/
