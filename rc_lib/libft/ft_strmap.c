/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 20:48:37 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:44:48 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	int		a;

	if (!s || !f)
		return (0);
	a = 0;
	str = malloc(ft_strlen((char*)s) + 1);
	while (s[a])
	{
		str[a] = (*f)(s[a]);
		a++;
	}
	str[a] = '\0';
	return (str);
}
