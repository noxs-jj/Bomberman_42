/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcm_min.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 14:40:20 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:52:58 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	rcm_min(double *values, int size)
{
	int				a;
	double			smalest_value;

	a = 1;
	if (!size)
		return (0);
	smalest_value = *values;
	while (a < size)
	{
		if (values[a] < smalest_value)
			smalest_value = values[a];
		a++;
	}
	return (smalest_value);
}
