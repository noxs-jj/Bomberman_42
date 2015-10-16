/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_setbright.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 14:27:23 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:14:35 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		color_setbright(int color, double c)
{
	unsigned int c1;
	unsigned int c2;

	if (c < 0)
		c = 0;
	if (c > 1)
		c = 1;
	c1 = 0xFF0000 & color;
	c1 = c1 >> 16;
	c1 *= c;
	c1 = c1 << 16;
	c2 = 0x00FF00 & color;
	c2 = c2 >> 8;
	c2 *= c;
	c2 = c2 << 8;
	return (c1 + c2 + (color & 0x0000FF) * c);
}
