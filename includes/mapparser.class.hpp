/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapparser.class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoiroux <jmoiroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/07 13:27:34 by jmoiroux          #+#    #+#             */
/*   Updated: 2015/11/07 13:45:52 by jmoiroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPPARSER_CLASS_HPP
# define MAPPARSER_CLASS_HPP

# include <ft42.class.hpp>


class Mapparser : public ft42 {
public:

  Mapparser();
  virtual ~Mapparser();

  Entity ***  map_from_file( char *map_path );
  Entity ***  map_alloc();

}

#endif
