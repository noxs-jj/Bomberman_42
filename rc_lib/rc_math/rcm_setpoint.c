/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcm_setpoint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/02 11:57:54 by rcargou           #+#    #+#             */
/*   Updated: 2015/10/02 11:58:38 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc_math.h"

t_point rcm_setpoint(float x, float y, float z)
{
	t_point new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}
