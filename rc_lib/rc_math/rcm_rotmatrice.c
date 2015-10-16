/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcm_rotmatrice.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 17:23:00 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/28 15:06:31 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc_math.h"
#include "math.h"
#include <stdio.h>

t_point		filepoint(double a, double b, double c)
{
	t_point new;

	new.x = a;
	new.y = b;
	new.z = c;
	return (new);
}

t_point		rcm_rotmatrice(t_point point, double rotx, double roty, double rotz)
{
	t_point tmp;

	tmp = filepoint(point.x, point.y, point.z);
	point.y = tmp.y * cos(rotx) + tmp.z * -sin(rotx);
	point.z = tmp.y * sin(rotx) + tmp.z * cos(rotx);
	tmp = filepoint(point.x, point.y, point.z);
	point.x = tmp.x * cos(rotz) + tmp.y * -sin(rotz);
	point.y = tmp.x * sin(rotz) + tmp.y * cos(rotz);
	tmp = filepoint(point.x, point.y, point.z);
	point.x = tmp.x * cos(roty) + tmp.z * sin(roty);
	point.z = tmp.x * -sin(roty) + tmp.z * cos(roty);
	return (point);
}
