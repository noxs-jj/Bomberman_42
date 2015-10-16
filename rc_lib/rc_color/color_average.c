/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_average.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 02:05:30 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:14:06 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int		color_average(int c1, int c2)
{
	int new;

	new = ((color_getcomp(c1, 'r') + color_getcomp(c2, 'r')) / 2) << 16;
	new += ((color_getcomp(c1, 'g') + color_getcomp(c2, 'g')) / 2) << 8;
	new += ((color_getcomp(c1, 'b') + color_getcomp(c2, 'b')) / 2);
	return (new);
}
