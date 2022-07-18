/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 00:32:30 by ndillon           #+#    #+#             */
/*   Updated: 2021/10/16 13:02:01 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_elem;
	t_list	*begin;
	t_list	*new_list;

	begin = NULL;
	new_list = NULL;
	while (lst)
	{
		new_elem = ft_lstnew(f(lst->content));
		if (!new_elem)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		lst = lst->next;
		if (!new_list)
		{
			new_list = new_elem;
			begin = new_list;
			continue ;
		}
		new_list->next = new_elem;
		new_list = new_list->next;
	}
	return (begin);
}
