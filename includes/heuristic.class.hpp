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

#ifndef Heuristic_CLASS_HPP
# define Heuristic_CLASS_HPP

# include <ft42.class.hpp>
# include <entity.class.hpp>

class Heuristic : public ft42 {
public:
    Heuristic( Heuristic const & src );
    Heuristic & operator=( Heuristic const & rhs );
    virtual ~Heuristic( void );
    Heuristic( void );

    int heuristic(std::vector<int> its);
};

#endif
