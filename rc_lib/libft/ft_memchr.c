/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 15:08:07 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:37:20 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t i;

	i = 0;
	if (s)
	{
		while (i < n)
		{
			if ((char)c == ((char *)s)[i])
				return (&((char *)s)[i]);
			i++;
		}
	}
	return (NULL);
}
