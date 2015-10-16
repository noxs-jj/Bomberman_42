/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsertsort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/10 01:57:14 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/03 15:45:58 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstinsertsort(t_list **start, int (*cmp)(t_list *a, t_list *b),
						t_list *elem)
{
	t_list *tmp;

	tmp = (*start);
	while (tmp && !cmp(elem, tmp))
		tmp = tmp->next;
	ft_lstinsert(start, elem, tmp);
}
