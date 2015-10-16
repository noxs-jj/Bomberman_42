/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcm_mulmatscalar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/29 15:35:29 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/29 15:40:27 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "rc_math.h"

float *rcm_mulmatscalar(float *mat, int count)
{
	float *new;

	count--;
	new = malloc(sizeof(float) * 16);
	memcpy(new, mat, sizeof(float) * 6);
	while (count > 0)
	{
		new = rcm_addmat(new, mat);
		count--;
	}
	return (new);
}
