// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Matrix.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 16:59:35 by rcargou           #+#    #+#             //
//   Updated: 2015/10/16 17:26:46 by rcargou          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MATRIX_HPP
# define MATRIX_HPP

# include <cmath>
# include <cstring>

class Matrix {

public :

    Matrix(void);

	~Matrix(void);

	void	rot_matrix(float x, float y, float z);
	void	trans_matrix(float x, float y, float z);
	void	mul_matrix(Matrix a, Matrix b);
	void	scale_matrix(float zoom);
	void	projection_matrix(float fov, float near, float fat, float aspect);
	void	identity_matrix(void);

	float *_matrix;
};

#endif
