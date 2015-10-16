/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/20 20:34:50 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:36:44 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	norme(t_list *tmp3, t_list *e1, t_list *e2)
{
	if (tmp3 && tmp3 != e1)
		tmp3->prev = e1;
	e1->next = tmp3;
	if (tmp3 == e1)
		e1->next = e2;
	if (e1->prev == e1)
		e1->prev = e2;
}

void	ft_lstswap(t_list **start, t_list *e1, t_list *e2)
{
	t_list *tmp2;
	t_list *tmp3;

	tmp2 = e2->prev;
	tmp3 = e2->next;
	e2->prev = e1->prev;
	if (e1->prev)
		e1->prev->next = e2;
	else
		(*start) = e2;
	if (e1->next && e1->next != e2)
		e1->next->prev = e2;
	e2->next = e1->next;
	if (e1->next == e2)
		e2->next = e1;
	if (e2->prev == e2)
		e2->prev = e1;
	e1->prev = tmp2;
	if (tmp2)
		tmp2->next = e1;
	else
		*start = e1;
	norme(tmp3, e1, e2);
}
