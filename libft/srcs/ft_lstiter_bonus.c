/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:33:15 by aprigent          #+#    #+#             */
/*   Updated: 2025/04/29 17:35:09 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	int		size;
	t_list	*temp;

	size = ft_lstsize(lst);
	while (size--)
	{
		temp = lst->next;
		f(lst->content);
		lst = temp;
	}
}
