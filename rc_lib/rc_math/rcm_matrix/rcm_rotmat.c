/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcm_rotmat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 17:12:28 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:02:30 by rcargou          ###   ########.fr       */
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
	ft_bzero(new, sizeof(float) * 16);
	new[5] = 1;
	new[15] = 1;
	new[0] = cos(rotz);
	new[8] = -sin(rotz);
	new[2] = sin(rotz);
	new[10] = cos(rotz);
	new2[0] = 1;
	new2[5] = cos(roty);
	new2[6] = -sin(roty);
	new2[9] = sin(roty);
	new2[10] = cos(roty);
	new2[15] = 1;
	new3[5] = cos(rotx);
	new3[6] = -sin(rotx);
	new3[9] = sin(rotx);
	new3[10] = cos(rotx);
	return (mulmat(mulmat(new, new2), new3));
}
