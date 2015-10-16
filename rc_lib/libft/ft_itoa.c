/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 14:16:02 by rcargou           #+#    #+#             */
/*   Updated: 2014/11/08 11:22:31 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static	int			count(int n)
{
	int a;

	a = 1;
	while (n /= 10)
		a++;
	return (a);
}

static char			*files_max_int(int n)
{
	char *str;

	str = malloc(sizeof(char) * 11);
	str = ft_itoa(-(n - 1));
	str[10]++;
	return (str);
}

char				*ft_itoa(int n)
{
	char	*str;
	int		a;

	a = count(n) + (n < 0) - 1;
	str = malloc(count(n) + (n < 0) + 1);
	str[count(n) + (n < 0) + 1] = 0;
	if (n == -2147483648)
		return (files_max_int(n));
	if (!n)
		str[0] = '0';
	if (n < 0)
	{
		n *= -1;
		str[0] = '-';
	}
	str[a + 1] = 0;
	while (n)
	{
		str[a--] = n % 10 + 48;
		n /= 10;
	}
	return (str);
}
