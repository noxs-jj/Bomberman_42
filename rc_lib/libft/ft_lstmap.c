/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 13:50:45 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:35:48 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *a;
	t_list *b;
	t_list *new_list;

	a = lst;
	if (!a && !f)
		return (0);
	a = f(lst);
	new_list = ft_lstnew(a->content, a->content_size);
	if (!new_list)
		return (0);
	b = new_list;
	while (lst->next)
	{
		a = f(lst->next);
		new_list->next = ft_lstnew(a->content, a->content_size);
		lst = lst->next;
		new_list = new_list->next;
	}
	return (b);
}
