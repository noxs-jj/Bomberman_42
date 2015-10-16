/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcm_sqrt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 01:12:31 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:53:05 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc_math.h"

double	rcm_sqrt(double n)
{
	double lr;
	double r;

	r = n;
	lr = r + 1;
	while (rcm_fabs(lr - r) > PRECISION)
	{
		lr = r;
		r = (lr + n / lr) / 2;
	}
	return (r);
}
