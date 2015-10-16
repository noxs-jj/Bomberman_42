// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Matrix.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 17:03:20 by rcargou           #+#    #+#             //
//   Updated: 2015/10/16 17:40:12 by rcargou          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

# include "Matrix.hpp"

Matrix::Matrix(void)
{
	identity_matrix();
}

Matrix::~Matrix(void)
{
	delete _matrix;
}

void Matrix::rot_matrix(float rotx, float roty, float rotz)
{
	Matrix	a;
	Matrix	b;
	Matrix	c;
	float	*new0;
	float	*new2;
	float	*new3;

	new0 = a._matrix;
	new2 = b._matrix;
	new3 = c._matrix;

	new0[0] = cos(rotz);
	new0[1] = -sin(rotz);
	new0[4] = sin(rotz);
	new0[5] = cos(rotz);

	new2[0] = cos(roty);
	new2[8] = -sin(roty);
	new2[2] = sin(roty);
	new2[10] = cos(roty);

	new3[5] = cos(rotx);
	new3[6] = -sin(rotx);
	new3[9] = sin(rotx);
	new3[10] = cos(rotx);
}

void Matrix::trans_matrix(float x, float y, float z)
{
	_matrix[3] = x;
	_matrix[7] = y;
	_matrix[11] = z;
}

void Matrix::mul_matrix(Matrix a, Matrix b)
{

	float *dst;
	float *s;
	float *t;

	dst = a._matrix;
	s = b._matrix;
	t = _matrix;
	memcpy(t, dst, 16 * sizeof(float));
	t[0] = dst[0] * s[0] + dst[4] * s[1] + dst[8] * s[2] + dst[12] * s[3];
	t[1] = dst[1] * s[0] + dst[5] * s[1] + dst[9] * s[2] + dst[13] * s[3];
	t[2] = dst[2] * s[0] + dst[6] * s[1] + dst[10] * s[2] + dst[14] * s[3];
	t[3] = dst[3] * s[0] + dst[7] * s[1] + dst[11] * s[2] + dst[15] * s[3];
	t[4] = dst[0] * s[4] + dst[4] * s[5] + dst[8] * s[6] + dst[12] * s[7];
	t[5] = dst[1] * s[4] + dst[5] * s[5] + dst[9] * s[6] + dst[13] * s[7];
	t[6] = dst[2] * s[4] + dst[6] * s[5] + dst[10] * s[6] + dst[14] * s[7];
	t[7] = dst[3] * s[4] + dst[7] * s[5] + dst[11] * s[6] + dst[15] * s[7];
	t[8] = dst[0] * s[8] + dst[4] * s[9] + dst[8] * s[10] + dst[12] * s[11];
	t[9] = dst[1] * s[8] + dst[5] * s[9] + dst[9] * s[10] + dst[13] * s[11];
	t[10] = dst[2] * s[8] + dst[6] * s[9] + dst[10] * s[10] + dst[14] * s[11];
	t[11] = dst[3] * s[8] + dst[7] * s[9] + dst[11] * s[10] + dst[15] * s[11];
	t[12] = dst[0] * s[12] + dst[4] * s[13] + dst[8] * s[14] + dst[12] * s[15];
	t[13] = dst[1] * s[12] + dst[5] * s[13] + dst[9] * s[14] + dst[13] * s[15];
	t[14] = dst[2] * s[12] + dst[6] * s[13] + dst[10] * s[14] + dst[14] * s[15];
	t[15] = dst[3] * s[12] + dst[7] * s[13] + dst[11] * s[14] + dst[15] * s[15];
}

void Matrix::scale_matrix(float zoom)
{

}

void Matrix::projection_matrix(float fov, float near, float far, float aspect)
{
	float   x_scale;
	float   y_scale;
	float   frustrum;

	identity_matrix();
	y_scale = (float)((1.0f / tan((fov / 2.0f) / 57.295)) * aspect);
	x_scale = y_scale / aspect;
	frustrum = far - near;
	_matrix[0] = x_scale;
	_matrix[5] = y_scale;
	_matrix[10] = -((far + near) / frustrum);
	_matrix[11] = -((2 * near * far) / frustrum);
	_matrix[14] = -1;
	_matrix[15] = 0;
}

void Matrix::identity_matrix(void)
{
	float	*m;

	_matrix = new float(16);
	m = _matrix;
	m[0] = 1;
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;
	m[4] = 0;
	m[5] = 1;
	m[6] = 0;
	m[7] = 0;
	m[8] = 0;
	m[9] = 0;
	m[10] = 1;
	m[11] = 0;
	m[12] = 0;
	m[13] = 0;
	m[14] = 0;
	m[15] = 1;
}

