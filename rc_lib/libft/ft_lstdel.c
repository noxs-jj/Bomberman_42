/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 12:31:10 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:34:40 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	if (del && alst)
	{
		while (*alst)
		{
			if ((*alst)->content)
				(del)((*alst)->content, (*alst)->content_size);
			(*alst) = (*alst)->next;
			free(*alst);
		}
		*alst = NULL;
	}
}
