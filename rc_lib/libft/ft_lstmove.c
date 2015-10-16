/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 17:06:20 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:36:01 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstmove(t_list **start, t_list *elem, t_list *loc)
{
	ft_lstsup(start, elem);
	ft_lstinsert(start, elem, loc);
}
