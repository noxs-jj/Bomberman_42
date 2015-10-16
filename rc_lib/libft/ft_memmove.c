/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 14:56:43 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:37:43 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	char	*cpy;

	cpy = (char*)malloc(sizeof(char) * n);
	cpy = ft_strncpy(cpy, s2, n);
	s1 = (void*)ft_strncpy(s1, cpy, n);
	free(cpy);
	return (s1);
}
