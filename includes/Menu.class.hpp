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

#ifndef MENU_CLASS_HPP
# define MENU_CLASS_HPP

# include <ft42.class.hpp>

enum MENU_SELECTED {
    RESUME_GAME = 0,
    MENU_CAMPAIGN,
    MENU_ARENA,
    MENU_MULTIPLAYER,
    MENU_CONFIG,
    MENU_CONFIG_SOUND,
    MENU_CONFIG_VIDEO,
    MENU_EXIT,

    MENU_CAMPAIGN_NEW,
    MENU_CAMPAIGN_CONTINUE,
    MENU_CAMPAIGN_COOP,
    MENU_CAMPAIGN_RETURN,
    MENU_ARENA_2P,
    MENU_ARENA_3P,
    MENU_ARENA_4P,
    MENU_ARENA_5P,
    MENU_ARENA_RETURN,
    MENU_MULTI_2P,
    MENU_MULTI_3P,
    MENU_MULTI_4P,
    MENU_MULTI_5P,
    MENU_MULTI_RETURN,
    MENU_CONFIG_PLAYER1,
    MENU_CONFIG_PLAYER2,
    MENU_CONFIG_PLAYER3,
    MENU_CONFIG_PLAYER4,
    MENU_CONFIG_PLAYER5,
    MENU_CONFIG_RETURN,
    MENU_CONFIG_SOUND_GLOBAL_SOUND,
    MENU_CONFIG_SOUND_SOUND_VOLUME,
    MENU_CONFIG_SOUND_RETURN,
    MENU_CONFIG_VIDEO_MODE,
    MENU_CONFIG_VIDEO_RESOLUTION,
    MENU_CONFIG_VIDEO_RETURN,
    MENU_EXIT_CONFIRM,
    MENU_EXIT_RETURN

};

enum MENU_SELECTED_PRINCIPAL {
    BIG_MENU = 0,
    CAMPAIGN,
    ARENA,
    MULTIPLAYER,
    CONFIG,
    CONFIG_SOUND,
    CONFIG_VIDEO,
    EXIT
};
class Event;

class Menu : public ft42 {
public:

    Event *         event;
    SDL_Surface *   current;
    SDL_Surface *   ecran_menu;
    bool            introstart;
    bool            launch_action;
    TTF_Font *      SansPosterBold;
    int             joystick_number = 0;

    SDL_Color       white;
    SDL_Color       blue;
    SDL_Color       red;
    SDL_Rect        position;

    int             menu_selected;
    int             detail_menu_selected;
    SDL_Surface *   str_return;
    SDL_Surface *   str_return_selected;
    SDL_Surface *   str_resume_game;
    SDL_Surface *   str_resume_game_selected;
    SDL_Surface *   str_campaign;
    SDL_Surface *   str_campaign_selected;
    SDL_Surface *   str_campaign_new;
    SDL_Surface *   str_campaign_new_selected;
    SDL_Surface *   str_campaign_coop;
    SDL_Surface *   str_campaign_coop_selected;
    SDL_Surface *   str_campaign_continue;
    SDL_Surface *   str_campaign_continue_selected;
    SDL_Surface *   str_arena;
    SDL_Surface *   str_arena_selected;
    SDL_Surface *   str_multiplayer;
    SDL_Surface *   str_multiplayer_selected;
    SDL_Surface *   str_2players;
    SDL_Surface *   str_2players_selected;
    SDL_Surface *   str_3players;
    SDL_Surface *   str_3players_selected;
    SDL_Surface *   str_4players;
    SDL_Surface *   str_4players_selected;
    SDL_Surface *   str_5players;
    SDL_Surface *   str_5players_selected;
    SDL_Surface *   str_config;
    SDL_Surface *   str_config_selected;
    SDL_Surface *   str_arcade;
    SDL_Surface *   str_arcade_selected;
    SDL_Surface *   str_exit;
    SDL_Surface *   str_exit_selected;
    SDL_Surface *   str_exit_confirm;
    SDL_Surface *   str_exit_confirm_selected;
    SDL_Surface *   str_player_controller_selected;
    SDL_Surface *   str_player_keyboard_selected;
    SDL_Surface *   str_config_1;
    SDL_Surface *   str_config_2;
    SDL_Surface *   str_config_3;
    SDL_Surface *   str_config_4;
    SDL_Surface *   str_config_5;
    SDL_Surface *   str_config_1_selected;
    SDL_Surface *   str_config_2_selected;
    SDL_Surface *   str_config_3_selected;
    SDL_Surface *   str_config_4_selected;
    SDL_Surface *   str_config_5_selected;
    SDL_Surface *   str_config_sound;
    SDL_Surface *   str_config_sound_selected;
    SDL_Surface *   str_config_sound_global_activated;
    SDL_Surface *   str_config_sound_global_activated_selected;
    SDL_Surface *   str_config_sound_global_desactivated;
    SDL_Surface *   str_config_sound_global_desactivated_selected;
    SDL_Surface *   str_config_sound_volume_off;
    SDL_Surface *   str_config_sound_volume_off_selected;
    SDL_Surface *   str_config_sound_colume_low;
    SDL_Surface *   str_config_sound_colume_low_selected;
    SDL_Surface *   str_config_sound_colume_medium;
    SDL_Surface *   str_config_sound_colume_medium_selected;
    SDL_Surface *   str_config_sound_colume_hight;
    SDL_Surface *   str_config_sound_colume_hight_selected;
    SDL_Surface *   str_config_sound_colume_default;
    SDL_Surface *   str_config_sound_colume_default_selected;
    SDL_Surface *   str_config_video;
    SDL_Surface *   str_config_video_selected;
    SDL_Surface *   str_config_video_fullscreen;
    SDL_Surface *   str_config_video_fullscreen_selected;
    SDL_Surface *   str_config_video_window;
    SDL_Surface *   str_config_video_window_selected;
    SDL_Surface *   str_config_video_800_600;
    SDL_Surface *   str_config_video_800_600_selected;
    SDL_Surface *   str_config_video_1280_720;
    SDL_Surface *   str_config_video_1280_720_selected;
    SDL_Surface *   str_config_video_1600_900;
    SDL_Surface *   str_config_video_1600_900_selected;
    SDL_Surface *   str_config_video_1920_1080;
    SDL_Surface *   str_config_video_1920_1080_selected;
    SDL_Surface *   str_config_video_2560_1440;
    SDL_Surface *   str_config_video_2560_1440_selected;
    SDL_Surface *   str_config_video_not_set;
    SDL_Surface *   str_config_video_not_set_selected;
    SDL_Surface *   str_config_video_not_set_disable;
    SDL_Surface *   str_option_disable;
    SDL_Surface *   str_option_disable_selected;
    SDL_Surface *   lose_campaign_txt;
    SDL_Surface *   winner_campaign_txt;
    SDL_Surface *   winner_game_txt;
    SDL_Surface *   winner_push_to_retry_previous;
    SDL_Surface *   winner_push_to_go_menu;
    SDL_Surface **  winner;

    bool            musicIsPlaying = false;     // pour fixer le probleme de la musique
                                                // dans le menu qui redemarre chaque millisecondes


    Menu(Event * event);
    virtual ~Menu();

    void            campaign();
    void            config();
    void            config_sound();
    void            config_video();
    void            arena();
    void            multiplayer();
    void            exit_game();
    void            exit_confirm();
    void            intro_start() ;
    void            main_loop();
    void            menu_keyboard();
    void            big_menu();
    void            init();
    void            print_surface(SDL_Surface * str, SDL_Surface * str_select, int x, int y, int type);
    void            move_menu_ver(int dir);
    void            menu_selection();
    void            change_menu();
    void            change_menu_back();
    void            winner_multi();
    void            winner_campaign();
    void            lose_campaign();
    void            end_campaign();
    void            move_menu_hor();

private:
    Menu( void );
    Menu( Menu const & src ) = delete;
    Menu & operator=( Menu const & rhs ) = delete;
};

#endif
