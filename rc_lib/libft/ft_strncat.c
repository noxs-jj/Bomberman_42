/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 15:54:02 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:44:59 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	unsigned int a;
	unsigned int len;

	a = 0;
	len = ft_strlen(s1);
	while (s2[a] && a < n)
	{
		s1[len + a] = s2[a];
		a++;
	}
	s1[a + len] = 0;
	return (s1);
}
