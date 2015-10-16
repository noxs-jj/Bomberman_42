/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_diff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 01:59:42 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:14:15 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int		color_diff(int c1, int c2)
{
	int a;

	a = (color_getcomp(c1, 'r') - color_getcomp(c2, 'r')
		+ color_getcomp(c1, 'b') - color_getcomp(c2, 'b')
		+ color_getcomp(c1, 'g') - color_getcomp(c2, 'g'));
	if (a < 0)
		a = -a;
	return (a);
}
