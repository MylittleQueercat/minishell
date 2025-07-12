/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:41:26 by aprigent          #+#    #+#             */
/*   Updated: 2025/04/29 18:05:57 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_head;
	t_list	*lst_tail;
	void	*temp;

	if (!lst)
		return (NULL);
	lst_head = NULL;
	while (lst)
	{
		temp = f(lst->content);
		lst_tail = ft_lstnew(temp);
		if (!lst_tail)
		{
			del(temp);
			return (ft_lstclear(&lst_head, del), NULL);
		}
		ft_lstadd_back(&lst_head, lst_tail);
		lst = lst->next;
	}
	return (lst_head);
}
