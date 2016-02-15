// ************************************************************************** //
//   24 Bomb                                                                  //
//   By: rcargou <rcargou@student.42.fr>                  :::      ::::::::   //
//   By: nmohamed <nmohamed@student.42.fr>              :+:      :+:    :+:   //
//   By: adjivas <adjivas@student.42.fr>              +:+ +:+         +:+     //
//   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        //
//   By: jmoiroux <jmoiroux@student.42.fr>        +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 17:03:20 by rcargou           #+#    #+#             //
//   Updated: 2015/10/27 14:00:02 by rcargou          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MATRIX_HPP
# define MATRIX_HPP

# include <cmath>
# include <cstring>
# include <ft42.class.hpp>

class Matrix {

public :

    Matrix(void);
	~Matrix(void);

	void			rot_matrix(float x, float y, float z);
	void			trans_matrix(float x, float y, float z);
	void			scale_matrix(float zoom);

	static Matrix	projection_matrix(float fov, float near, float fat, float aspect);
	static Matrix	view_matrix(t_point pos, t_point dir, float zoom);
	static Matrix	model_matrix(t_point pos, t_point dir, float zoom);

	void			identity_matrix(void);

	Matrix operator*(Matrix & src);
	Matrix operator=(Matrix src);

	float _matrix[16];
};

std::ostream & operator<<(std::ostream  & o, Matrix & src);

#endif
