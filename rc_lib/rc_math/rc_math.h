/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 00:49:59 by rcargou           #+#    #+#             */
/*   Updated: 2015/10/02 12:04:41 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RC_MATH_H
# define RC_MATH_H
# define PI 3.1415926535897932384626433832795
# define PRECISION 1E-6
# include <stdlib.h>
# include <math.h>

typedef struct	s_point
{
	double		x;
	double		y;
	double		z;
}				t_point;
int				rcm_veqec(t_point a, t_point b);
double			rcm_vecsquarelength(t_point vec);
t_point			rcm_crossproduct(t_point a, t_point b);
double			rcm_sqrt(double n);
double			rcm_fabs(double n);
t_point			rcm_vecsum(t_point vec1, t_point vec2);
double			rcm_min(double *values, int size);
t_point			rcm_vecscalarfactor(t_point vec, double factor);
double			*rcm_2dequation(double a, double b, double c, int *n);
t_point			rcm_vecnormalize(t_point vec);
t_point			rcm_rotmatrice(t_point point, double rotx, double roty,
					double rotz);
double			rcm_vecnorme(t_point vec);
t_point			rcm_vecneg(t_point vec);
double			rcm_dotproduct(t_point a, t_point b);
t_point			rcm_vecsub(t_point v1, t_point v2);
t_point			rcm_vecproject(t_point a, t_point b);
float			*rcm_transmat(float x, float y, float z);
float			*rcm_scalemat(float scale);
float			*rcm_rotmat(float rotx, float roty, float rotz);
float			*rcm_projectmat(float fov, float near, float far, float aspect);
float			*rcm_mulmat(float *dst, float *s);
float			*rcm_identitymat(void);
float			*rcm_mulmatscalar(float *a, int b);
float			*rcm_addmat(float *a, float *b);
t_point			rcm_setpoint(float a, float b, float c);
#endif
