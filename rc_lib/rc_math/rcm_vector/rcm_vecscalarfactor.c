/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcm_vecscalarfactor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 02:39:15 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:04:41 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc_math.h"

t_point		rcm_vecscalarfactor(t_point vec, double factor)
{
	vec.x *= factor;
	vec.y *= factor;
	vec.z *= factor;
	return (vec);
}
