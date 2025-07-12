/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:31:34 by aprigent          #+#    #+#             */
/*   Updated: 2025/04/30 11:46:39 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isinset(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = ft_strlen(s1) - 1;
	while (s1[++i])
	{
		if (!isinset(s1[i], set))
			break ;
	}
	while (j >= 0 && isinset(s1[j], set))
		j--;
	if (j - i + 2 <= 0)
		return (ft_calloc(1, 1));
	str = malloc(j - i + 2);
	if (!str)
		return (NULL);
	i--;
	k = -1;
	while (++k >= 0 && ++i <= j)
		str[k] = s1[i];
	str[k] = 0;
	return (str);
}
/*
int main()
{
 	printf("%s\n", ft_strtrim("   xxx   xxx", " x"));
}*/
