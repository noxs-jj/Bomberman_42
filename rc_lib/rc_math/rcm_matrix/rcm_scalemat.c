/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcm_scalemat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 17:10:45 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 14:58:11 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc_math.h"
#include "../libft/libft.h"

float	*rcm_scalemat(float scale)
{
	float *new;

	new = malloc(sizeof(float) * 16);
	ft_bzero(new, sizeof(float) * 16);
	new[15] = 1;
	new[0] = scale;
	new[5] = scale;
	new[10] = scale;
	return (new);
}
