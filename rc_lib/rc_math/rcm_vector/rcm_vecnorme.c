/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcm_vecnorme.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 14:37:12 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:04:22 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc_math.h"

double	rcm_vecnorme(t_point vec)
{
	return (rcm_sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}
