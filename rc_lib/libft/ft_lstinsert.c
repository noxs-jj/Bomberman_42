/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 16:43:01 by rcargou           #+#    #+#             */
/*   Updated: 2015/03/22 17:19:36 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_lstinsert(t_list **start, t_list *elem, t_list *loc)
{
	elem->prev = loc;
	if (loc)
	{
		elem->next = loc->next;
		loc->next = elem;
	}
	else
	{
		elem->next = (*start);
		*start = elem;
	}
	if (elem->next)
		elem->next->prev = elem;
}
