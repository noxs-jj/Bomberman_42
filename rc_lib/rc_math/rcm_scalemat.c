/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcm_scalemat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 17:10:45 by rcargou           #+#    #+#             */
/*   Updated: 2015/10/05 03:14:19 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc_math.h"
#include "../libft/libft.h"

float	*rcm_scalemat(float scale)
{
	float *new;

	new = rcm_identitymat();
	new[15] = 1;
	new[0] = scale;
	new[5] = scale;
	new[10] = scale;
	return (new);
}
