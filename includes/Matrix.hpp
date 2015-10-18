// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Matrix.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 16:59:35 by rcargou           #+#    #+#             //
/*   Updated: 2015/10/18 18:55:38 by rcargou          ###   ########.fr       */
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
	static Matrix	view_matrix(t_point pos, t_point dir);
	static Matrix	model_matrix(t_point pos, t_point dir);

	void			identity_matrix(void);

	Matrix operator*(Matrix & src);
	Matrix operator=(Matrix src);

	float *_matrix;
};

std::ostream & operator<<(std::ostream  & o, Matrix & src);

#endif
