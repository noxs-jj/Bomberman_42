/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcm_2dequation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 01:00:47 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:52:44 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc_math.h"

double	*rcm_2dequation(double a, double b, double c, int *n)
{
	double	delta;
	double	*solutions;

	delta = b * b - 4 * a * c;
	if (delta < 0)
	{
		*n = 0;
		return (NULL);
	}
	else if (delta == 0)
	{
		*n = 1;
		solutions = malloc(sizeof(double));
		*solutions = -b / (2 * a);
		return (solutions);
	}
	solutions = malloc(sizeof(double) * 2);
	solutions[0] = (rcm_sqrt(delta) - b) / (2 * a);
	solutions[1] = (rcm_sqrt(delta) + b) / (2 * a);
	*n = 2;
	return (solutions);
}
