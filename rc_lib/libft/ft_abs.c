/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 12:24:56 by rcargou           #+#    #+#             */
/*   Updated: 2015/09/02 15:31:54 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}
