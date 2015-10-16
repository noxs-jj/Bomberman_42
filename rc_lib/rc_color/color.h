/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 14:58:21 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/28 15:08:48 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

int				color_add(int color1, int color2);
int				color_getcomp(int color, char c);
int				color_setbright(int color, double c);
int				color_diff(int c1, int c2);
int				color_average(int c1, int c2);
#endif
