/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlenbase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/24 18:04:57 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:39:15 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nbrlenbase(long int n, int base)
{
	int len;

	len = 0 + !n;
	while (n)
	{
		n = n / base;
		len++;
	}
	return (len);
}
