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

#ifndef SAVE_CLASS_HPP
# define SAVE_CLASS_HPP

# include <ft42.class.hpp>
# define GLOBAL_CONFIG_FILE "config/.save_config"

class Save : public ft42 {
public:
    t_global_config global_config;

    Save();
    virtual ~Save();

    void    fill_info_config( void );
    void    print_config_debugg( void );
    void    fill_actual_resolution( void );
    void    save_level(int level);
    void    load_level( void );
    void    save_global_config_to_file( void );
    void    load_global_config_file( void );

};

#endif
