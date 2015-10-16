/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcm_rotmat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 17:12:28 by rcargou           #+#    #+#             */
/*   Updated: 2015/10/04 23:59:50 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc_math.h"
#include "../libft/libft.h"

float	*rcm_rotmat(float rotx, float roty, float rotz)
{
	float *new;
	float *new2;
	float *new3;

	new3 = rcm_identitymat();
	new = rcm_identitymat();
	new2 = rcm_identitymat();
	new[0] = cos(rotz);
	new[1] = -sin(rotz);
	new[4] = sin(rotz);
	new[5] = cos(rotz);

	new2[0] = cos(roty);
	new2[8] = -sin(roty);
	new2[2] = sin(roty);
	new2[10] = cos(roty);

	new3[5] = cos(rotx);
	new3[6] = -sin(rotx);
	new3[9] = sin(rotx);
	new3[10] = cos(rotx);
	return (rcm_mulmat(rcm_mulmat(new, new2), new3));
}
