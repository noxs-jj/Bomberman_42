/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/15 15:44:49 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:34:57 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstfind(t_list **lst, t_list *elem)
{
	t_list *tmp;

	if (!lst || !*lst)
		return (0);
	tmp = *lst;
	while (tmp != (*lst)->prev)
	{
		if (tmp == elem)
			return (1);
		tmp = tmp->next;
	}
	if (tmp == elem)
		return (1);
	return (0);
}
