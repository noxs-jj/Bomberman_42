/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 15:45:05 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:41:56 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int a;
	int len;

	a = 0;
	len = ft_strlen(s1);
	while (s2[a])
	{
		s1[len + a] = s2[a];
		a++;
	}
	s1[len + a] = 0;
	return (s1);
}
