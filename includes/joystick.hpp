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

#ifndef JOYSTICK_HPP
# define JOYSTICK_HPP

# include <ft42.class.hpp>

class Joystick : public ft42 {
public:
    int                timer;
    int                test = 0;
    SDL_Joystick *     manette1 = NULL;
    SDL_Joystick *     manette2 = NULL;
    SDL_Joystick *     manette3 = NULL;
    SDL_Joystick *     manette4 = NULL;
    SDL_Joystick *     manette5 = NULL;
    int                config[5]; // 0: controller, 1: keyboard
    t_key *            arr_key_keyboard[5];
    t_key *            arr_key_controller[5];

    Joystick(void);
    virtual ~Joystick( void );

    void    read_key(int mode);
    void    change_dir_joystick(t_key *key, int dir);
    void    load_config( void );
    void    save_config( void );
    void    save_default_config( void );
    void    set_key_config();
    void    set_key();
    void    init_joystick();
		void 		reset_key_pressed();
		void 		refresh_all_dir_joystick();
		void 		refresh_dir_joystick(t_key *key, Sint16 x_move, Sint16 y_move);

private:
    Joystick( Joystick const & src );
    Joystick & operator=( Joystick const & rhs );
};

#endif
