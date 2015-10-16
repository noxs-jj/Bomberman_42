/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 19:13:40 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:46:36 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strnew(size_t size)
{
	char				*str;
	unsigned int		a;

	a = 0;
	str = malloc(sizeof(char) * size);
	if (!str)
		return (0);
	while (a <= size)
	{
		str[a] = 0;
		a++;
	}
	return (str);
}
