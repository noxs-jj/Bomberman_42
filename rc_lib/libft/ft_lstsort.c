/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 16:29:21 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/06 14:42:45 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		sorted(t_list *a, t_list *b, int (*cmp)(t_list *a, t_list *b))
{
	while (a != b)
	{
		if (b)
			if (cmp(a, b))
				return (0);
		a = a->next;
	}
	return (1);
}

t_list	*norme(t_list **i, t_list **j, t_list *elem, t_list **first)
{
	*first = elem;
	*i = elem;
	*j = elem;
	return (elem);
}

void	quicksort(t_list **start, t_list *elem, t_list *end,
			int (*cmp)(t_list *a, t_list *b))
{
	t_list *j;
	t_list *i;
	t_list *pivot;
	t_list *first;

	pivot = norme(&i, &j, elem, &first);
	if (elem == NULL || elem == end)
		return ;
	while (j && j != end)
	{
		if (j != pivot && cmp(j, pivot))
		{
			if (first == elem)
				first = j;
			ft_lstmove(start, j, elem->prev);
			j = i;
		}
		i = j;
		j = j->next;
	}
	if (!sorted(first, pivot, cmp))
		quicksort(start, first, pivot, cmp);
	if (!sorted(pivot->next, end, cmp))
		quicksort(start, pivot->next, end, cmp);
}

void	ft_lstsort(t_list **start, int (*cmp)(t_list *a, t_list *b))
{
	quicksort(start, *start, NULL, cmp);
}
