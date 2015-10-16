/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 20:55:38 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:45:08 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		a;

	if (!s || !f)
		return (0);
	a = 0;
	str = malloc(ft_strlen(s));
	while (s[a])
	{
		str[a] = (*f)(a, s[a]);
		a++;
	}
	return (str);
}
