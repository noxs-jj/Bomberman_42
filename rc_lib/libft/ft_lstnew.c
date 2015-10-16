/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 11:43:03 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:36:17 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *new;

	new = malloc(sizeof(t_list));
	new->content = malloc((content_size));
	if (content)
		new->content = ft_memcpy(new->content, (void*)content, content_size);
	new->content_size = content_size;
	if (!content)
		new->content_size = 0;
	new->next = 0;
	new->prev = 0;
	return (new);
}
