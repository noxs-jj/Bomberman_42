/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dectobin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/04 20:45:26 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:33:12 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_dectobin(int n)
{
	int new;
	int a;

	a = 0;
	new = 0;
	while (n)
	{
		new *= 10;
		if (!new)
			a++;
		new += ((n % 2));
		n /= 2;
	}
	new *= ft_pow(10, a - 1);
	return (ft_atoi(ft_strrev(ft_itoa(new))));
}
