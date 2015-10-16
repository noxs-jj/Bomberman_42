/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpynew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/10 02:47:43 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:34:27 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

t_list	*ft_lstcpynew(void *content, size_t size)
{
	t_list *new;

	new = malloc(sizeof(t_list));
	new->next = NULL;
	new->prev = NULL;
	new->content = content;
	new->content_size = size;
	return (new);
}
