/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_backchrfils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/04 19:43:01 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:32:44 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_backchrfils(char *s1, char *s2, char c)
{
	int i;
	int j;

	i = ft_strlen(s1) - 1;
	j = ft_strlen(s2) - 1;
	while (i > -1 && j > -1)
	{
		if (s1[i] == c)
		{
			s1[i] = s2[j];
			j--;
		}
		i--;
	}
	return (s1);
}
