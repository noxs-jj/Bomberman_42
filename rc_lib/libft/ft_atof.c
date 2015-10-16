/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 19:25:32 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:32:33 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

float	ft_atof(char *str)
{
	float		new;
	float		tmp;
	char		*stmp;
	int			i;

	i = 0;
	new = ft_atoi(str);
	stmp = ft_strchr(str, '.');
	if (stmp)
	{
		stmp++;
		tmp = ft_atoi(stmp);
		while (tmp > 1)
		{
			tmp /= 10;
		}
		while (stmp[i] == '0')
		{
			tmp /= 10;
			i++;
		}
		new += tmp;
	}
	return (new);
}
