/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcm_addmat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/29 15:31:54 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/29 15:34:49 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rc_math.h"
# include <string.h>

float *rcm_addmat(float *m1, float *m2)
{
	float		*new;
	int			i;

	new = malloc(sizeof(float) * 16);
	memcpy(new, m1, sizeof(float) * 16);
	i = 0;
	while (i < 16)
	{
		new[i] += m2[i];
		i++;
	}
	return (new);
}
