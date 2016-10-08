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
    int                 timer;
    int                 test = 0;

    SDL_Joystick **     manettes;

    int                 config[10]; // 0: controller, 1: keyboard
    t_key *             arr_key_keyboard[5];
    t_key *             arr_key_controller[10];

    Joystick(void);
    virtual ~Joystick( void );

    void        read_key(int mode);
    void        change_dir_joystick(t_key *key, int dir);
    void        load_config( void );
    void        save_config( void );
    void        save_default_config( void );
    void        set_key_config();
    void        set_key();
    void        init_joystick();
    void        reset_key_pressed();
    void        refresh_all_dir_joystick();
    void        refresh_dir_joystick(t_key *key, Sint16 x_move, Sint16 y_move);
    static void intro_read_key();
    static void intro_pass();
    void        in_menu_SDLK_RETURN();
    void        in_menu_SDLK_p();
    void        in_menu_SDLK_k();
    void        in_menu_SDLK_u();
    void        in_menu_SDLK_1();
    void        in_menu_SDLK_2();
    void        in_menu_SDLK_3();
    void        in_menu_controller_3();
    void        in_menu_controller_9();
    void        in_menu_controller_axis_motion(SDL_Event &event);
    void        in_menu_controller_hat_motion(SDL_Event &event);
    void        in_game_SDLK_RETURN();
    void        in_game_SDLK_k();
    void        in_game_SDLK_p();
    void        in_game_controller_8();
    void        in_game_controller_9(SDL_Event &event);
    void        in_game_controller_axis_motion(SDL_Event &event);
    void        in_game_controller_hat_motion(SDL_Event &event);

private:
    Joystick( Joystick const & src );
    Joystick & operator=( Joystick const & rhs );
};

#endif
