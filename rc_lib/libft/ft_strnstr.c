/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 16:41:35 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:49:17 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	char				*tmp;
	unsigned int		a;
	int					b;

	if (!s2[0])
		return (&(((char*)s1)[0]));
	if (!s1[0] && s2[0])
		return (0);
	a = 0;
	b = 0;
	tmp = (char*)s1;
	while (tmp[a] != '\0' && a < n)
	{
		if (tmp[a] == s2[b])
			b++;
		else
			b = 0;
		a++;
		if (s2[b] == '\0')
			return (&(tmp[a - b]));
	}
	return (0);
}
