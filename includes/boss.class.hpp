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

#ifndef BOSS_CLASS_HPP
# define BOSS_CLASS_HPP

# include <entity.class.hpp>
class Entity;

class Boss : public Entity {
public:

    int    name;

    Boss( float x, float y, int status, int name, int model );
    Boss( Boss const & src );
    Boss & operator=( Boss const & rhs );
    virtual ~Boss( void );

private:
    Boss( void );
};

#endif

// Bureaucrat::Bureaucrat(Bureaucrat const & rSource) {
// 	*this = rSource;
// }
//
// Bureaucrat & 		Bureaucrat::operator=(Bureaucrat const & rSource) {
// 	if ( this != &rSource ) {
// 		(std::string)this->_name = rSource.getName();
// 		this->_grade = rSource.getGrade();
// 	}
// 	return *this;
// }
//
// Bomb( Bomb const & src );
// Bomb & Bomb::operator=( Bomb const & rhs );
//
// Bomb::Bomb( Bomb const & src ) {
//     *this = src;
// }
//
// Bomb & operator=( Bomb const & rhs ) {
//     if (this != &rhs) {
//         this->timer = rhs.timer;
//         this->creator_id = rhs.creator_id;
//         this->pushed = rhs.pushed;
//         this->pushed_dir = rhs.pushed_dir;
//     }
//     return *this;
// }
