/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 12:37:41 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:34:20 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (alst && new)
	{
		if (!*alst)
		{
			*alst = new;
			return ;
		}
		(*alst)->prev = new;
		new->next = *alst;
		*alst = new;
		new->prev = NULL;
	}
}
