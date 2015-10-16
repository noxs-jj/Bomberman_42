/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcm_vecnormalise.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 16:43:51 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:04:02 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc_math.h"

t_point		rcm_vecnormalize(t_point vec)
{
	double a;

	a = rcm_vecnorme(vec);
	vec.x /= a;
	vec.y /= a;
	vec.z /= a;
	return (vec);
}
