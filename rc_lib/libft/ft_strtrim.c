/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 10:11:51 by rcargou           #+#    #+#             */
/*   Updated: 2014/11/08 11:37:10 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		is_white(char c)
{
	return (c == ',' || c == ' ' || c == '\n' || c == '\t');
}

char			*ft_strtrim(char const *s)
{
	int		a;
	int		b;
	int		c;
	char	*new_str;

	if (!s)
		return (0);
	a = 0;
	b = ft_strlen((char*)s) - 1;
	while (is_white(s[a]))
		a++;
	while (is_white(s[b]) && b && b > a)
		b--;
	new_str = malloc(ft_strlen((char*)s) * (b - a + 2));
	if (!new_str)
		return (0);
	c = a;
	while (a <= b)
	{
		new_str[a - c] = s[a];
		a++;
	}
	new_str[b + 1] = 0;
	return (new_str);
}
