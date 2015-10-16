/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcm_transmat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 18:11:25 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:02:36 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc_math.h"

float	*rcm_transmat(float x, float y, float z)
{
	float *new;

	new = rcm_identitymat();
	new[3] = x;
	new[7] = y;
	new[11] = z;
	return (new);
}
