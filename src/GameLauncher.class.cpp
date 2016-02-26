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

#include <GameLauncher.class.hpp>
#include <event.class.hpp>
#include <soundrender.class.hpp>
#include <map_event.class.hpp>

void  Gamelauncher::intro_lauch_game() {
    main_event->w_log("INTRO LAUNCH BINAIRE");
    main_event->soundrender->stopMusic();
    main_event->soundrender->playMusic("ps1");
    main_event->draw_winner_multi = -1;
    main_event->draw_winner_campaign = -1;
    main_event->draw_lose_campaign = -1;
    main_event->draw_end_campaign = -1;
    main_event->actual_level = 0;
    main_event->intro_map = true;
    main_event->coop = 0;
    main_event->multi = 0;
    main_event->arena = 0;
    main_event->mode_menu = false; // desactive menu render
    main_event->make_new_game(0);
    main_event->game_playing = true; // activate active partie
}

void    Gamelauncher::campaign_new() {
    main_event->w_log("MENU_CAMPAIGN_NEW + LAUNCH ");
    main_event->draw_winner_multi = -1;
    main_event->draw_winner_campaign = -1;
    main_event->draw_lose_campaign = -1;
    main_event->draw_end_campaign = -1;
    main_event->actual_level = 1;
    main_event->coop = 0;
    main_event->multi = 0;
    main_event->arena = 0;
    main_event->intro_map = false;
    main_event->mode_menu = false; // desactive menu render
    main_event->make_new_game(0);
    main_event->game_playing = true; // activate active partie
}

void Gamelauncher::campaign_continue() {
    main_event->w_log("MENU_CAMPAIGN_CONTINUE + LAUNCH ");
    main_event->draw_winner_multi = -1;
    main_event->draw_winner_campaign = -1;
    main_event->draw_lose_campaign = -1;
    main_event->draw_end_campaign = -1;
    main_event->actual_level = main_event->save_level;
    if (main_event->save_level_mode == false)
        main_event->coop = 0;
    else
        main_event->coop = 2;
    main_event->multi = 0;
    main_event->arena = 0;
    main_event->intro_map = false;
    main_event->mode_menu = false; // desactive menu render
    main_event->make_new_game(0);
    main_event->game_playing = true; // activate active partie

}

void    Gamelauncher::campaign_new_coop() {
    main_event->w_log("MENU_CAMPAIGN_NEW_COOP + LAUNCH ");
    main_event->draw_winner_multi = -1;
    main_event->draw_winner_campaign = -1;
    main_event->draw_lose_campaign = -1;
    main_event->draw_end_campaign = -1;
    main_event->actual_level = 1;
    main_event->coop = 2;
    main_event->multi = 0;
    main_event->arena = 0;
    main_event->intro_map = false;
    main_event->mode_menu = false; // desactive menu render
    main_event->make_new_game(0);
    main_event->game_playing = true; // activate active partie
}

void    Gamelauncher::run_multi_2() {
    main_event->w_log("MENU_MULTIPLAYER + MENU_MULTI_2P + LAUNCH ");
    main_event->soundrender->stopMusic();
    main_event->soundrender->playSound("dogsout_long");
    main_event->draw_winner_multi = -1;
    main_event->draw_winner_campaign = -1;
    main_event->draw_lose_campaign = -1;
    main_event->draw_end_campaign = -1;
    main_event->coop = 0;
    main_event->multi = 2; // 2 players in game
    main_event->arena = 0;
    main_event->intro_map = false;
    main_event->mode_menu = false; // desactive menu render
    main_event->make_new_game(0);
    main_event->game_playing = true; // activate active partie
}

void    Gamelauncher::run_multi_3() {
    main_event->w_log("MENU_MULTIPLAYER + MENU_MULTI_3P + LAUNCH ");
    main_event->w_log("MENU_MULTIPLAYER + MENU_MULTI_2P + LAUNCH ");
    main_event->soundrender->stopMusic();
    main_event->soundrender->playSound("dogsout_long");
    main_event->draw_winner_multi = -1;
    main_event->draw_winner_campaign = -1;
    main_event->draw_lose_campaign = -1;
    main_event->draw_end_campaign = -1;
    main_event->coop = 0;
    main_event->multi = 3; // 3 players in game
    main_event->arena = 0;
    main_event->intro_map = false;
    main_event->mode_menu = false; // desactive menu render
    main_event->make_new_game(0);
    main_event->game_playing = true; // activate active partie
}

void    Gamelauncher::run_multi_4() {
    main_event->w_log("MENU_MULTIPLAYER + MENU_MULTI_4P + LAUNCH ");
    main_event->w_log("MENU_MULTIPLAYER + MENU_MULTI_2P + LAUNCH ");
    main_event->soundrender->stopMusic();
    main_event->soundrender->playSound("dogsout_long");
    main_event->draw_winner_multi = -1;
    main_event->draw_winner_campaign = -1;
    main_event->draw_lose_campaign = -1;
    main_event->draw_end_campaign = -1;
    main_event->coop = 0;
    main_event->multi = 4; // 4 players in game
    main_event->arena = 0;
    main_event->intro_map = false;
    main_event->mode_menu = false; // desactive menu render
    main_event->make_new_game(0);
    main_event->game_playing = true; // activate active partie
}

void    Gamelauncher::run_multi_5() {
    main_event->w_log("MENU_MULTIPLAYER + MENU_MULTI_5P + LAUNCH ");
    main_event->w_log("MENU_MULTIPLAYER + MENU_MULTI_2P + LAUNCH ");
    main_event->soundrender->stopMusic();
    main_event->soundrender->playSound("dogsout_long");
    main_event->draw_winner_multi = -1;
    main_event->draw_winner_campaign = -1;
    main_event->draw_lose_campaign = -1;
    main_event->draw_end_campaign = -1;
    main_event->coop = 0;
    main_event->multi = 5; // 4 players in game
    main_event->arena = 0;
    main_event->intro_map = false;
    main_event->mode_menu = false; // desactive menu render
    main_event->make_new_game(0);
    main_event->game_playing = true; // activate active partie
}

void    Gamelauncher::run_arena_2() {
    main_event->w_log("MENU_MULTIPLAYER + MENU_ARENA_2P + LAUNCH ");
    main_event->w_log("MENU_MULTIPLAYER + MENU_MULTI_2P + LAUNCH ");
    main_event->soundrender->stopMusic();
    main_event->soundrender->playMusic("music_boss");
    main_event->draw_winner_multi = -1;
    main_event->draw_winner_campaign = -1;
    main_event->draw_lose_campaign = -1;
    main_event->draw_end_campaign = -1;
    main_event->coop = 0;
    main_event->multi = 0;
    main_event->arena = 2;  // 2 players in game
    main_event->intro_map = false;
    main_event->mode_menu = false; // desactive menu render
    main_event->make_new_game(0);
    main_event->game_playing = true; // activate active partie
}

void    Gamelauncher::run_arena_3() {
    main_event->w_log("MENU_MULTIPLAYER + MENU_ARENA_3P + LAUNCH ");
    main_event->w_log("MENU_MULTIPLAYER + MENU_MULTI_2P + LAUNCH ");
    main_event->soundrender->stopMusic();
    main_event->soundrender->playMusic("music_boss");
    main_event->draw_winner_multi = -1;
    main_event->draw_winner_campaign = -1;
    main_event->draw_lose_campaign = -1;
    main_event->draw_end_campaign = -1;
    main_event->coop = 0;
    main_event->multi = 0;
    main_event->arena = 3;  // 3 players in game
    main_event->intro_map = false;
    main_event->mode_menu = false; // desactive menu render
    main_event->make_new_game(0);
    main_event->game_playing = true; // activate active partie
}

void    Gamelauncher::run_arena_4() {
    main_event->w_log("MENU_MULTIPLAYER + MENU_ARENA_4P + LAUNCH ");
    main_event->w_log("MENU_MULTIPLAYER + MENU_MULTI_2P + LAUNCH ");
    main_event->soundrender->stopMusic();
    main_event->soundrender->playMusic("music_boss");
    main_event->draw_winner_multi = -1;
    main_event->draw_winner_campaign = -1;
    main_event->draw_lose_campaign = -1;
    main_event->draw_end_campaign = -1;
    main_event->coop = 0;
    main_event->multi = 0;
    main_event->arena = 4;  // 4 players in game
    main_event->intro_map = false;
    main_event->mode_menu = false; // desactive menu render
    main_event->make_new_game(0);
    main_event->game_playing = true; // activate active partie
}

void    Gamelauncher::run_arena_5() {
    main_event->w_log("MENU_MULTIPLAYER + MENU_ARENA_5P + LAUNCH ");
    main_event->w_log("MENU_MULTIPLAYER + MENU_MULTI_2P + LAUNCH ");
    main_event->soundrender->stopMusic();
    main_event->soundrender->playMusic("music_boss");
    main_event->draw_winner_multi = -1;
    main_event->draw_winner_campaign = -1;
    main_event->draw_lose_campaign = -1;
    main_event->draw_end_campaign = -1;
    main_event->coop = 0;
    main_event->multi = 0;
    main_event->arena = 5;  // 4 players in game
    main_event->intro_map = false;
    main_event->mode_menu = false; // desactive menu render
    main_event->make_new_game(0);
    main_event->game_playing = true; // activate active partie
}

void    Gamelauncher::retry_previous_game() {
    if (5 == main_event->multi)
        Gamelauncher::run_multi_5();
    else if (4 == main_event->multi)
        Gamelauncher::run_multi_4();
    else if (3 == main_event->multi)
        Gamelauncher::run_multi_3();
    else if (2 == main_event->multi)
        Gamelauncher::run_multi_2();
    else if (5 == main_event->arena)
        Gamelauncher::run_arena_5();
    else if (4 == main_event->arena)
        Gamelauncher::run_arena_4();
    else if (3 == main_event->arena)
        Gamelauncher::run_arena_3();
    else if (2 == main_event->arena)
        Gamelauncher::run_arena_2();
}

Gamelauncher::Gamelauncher() {}

Gamelauncher::~Gamelauncher() {}
