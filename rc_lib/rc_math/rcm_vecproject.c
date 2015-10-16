/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcm_vecproject.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 15:51:14 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:04:30 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc_math.h"

t_point		rcm_vecproject(t_point a, t_point b)
{
	t_point new;

	new = rcm_vecscalarfactor(b, rcm_dotproduct(a, b)
		/ rcm_dotproduct(b, b));
	return (new);
}
