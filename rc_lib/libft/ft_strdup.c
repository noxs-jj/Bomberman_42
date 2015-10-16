/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 15:29:19 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:42:57 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		a;

	a = 0;
	dest = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (dest)
	{
		while (s1[a])
		{
			dest[a] = s1[a];
			a++;
		}
	}
	dest[a] = 0;
	return (dest);
}
