/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/16 17:03:20 by rcargou           #+#    #+#             */
/*   Updated: 2016/02/04 17:48:24 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_CLASS_HPP
# define BONUS_CLASS_HPP

# include <entity.class.hpp>

class entity;
class Bonus : public Entity {
public:
	int		timer;

	Bonus( float x, float y, int status, int model );
	Bonus( Bonus const & src );
	Bonus & operator=( Bonus const & rhs );
	virtual ~Bonus( void );
	void	affect(Entity *ent);
	void change_bomb(Entity *ent);
private:
	Bonus( void );
};

#endif
