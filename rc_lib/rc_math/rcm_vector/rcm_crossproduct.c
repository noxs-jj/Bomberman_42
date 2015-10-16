/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcm_crossproduct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 21:04:28 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:03:11 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc_math.h"

t_point		rcm_crossproduct(t_point a, t_point b)
{
	t_point new;

	new.x = a.y * b.z - b.y * a.z;
	new.y = a.z * b.x - b.z * a.x;
	new.z = a.x * b.y - b.x * a.y;
	return (new);
}
