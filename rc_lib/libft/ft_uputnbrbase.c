/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uputnbrbase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/31 17:39:56 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:48:03 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_unputnbrbase(unsigned long int n, char *alphabet, int widht)
{
	unsigned long int base;

	widht -= ft_nbrlenbase(n, ft_strlen(alphabet));
	while (widht-- > 0)
		write(1, "0", 1);
	base = ft_strlen(alphabet);
	if (n >= base)
		ft_unputnbrbase(n / base, alphabet, 0);
	write(1, &(alphabet[n % base]), 1);
}
