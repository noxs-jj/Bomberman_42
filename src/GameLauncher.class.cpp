/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameLauncher.class.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/16 17:03:20 by rcargou           #+#    #+#             */
/*   Updated: 2016/02/05 14:17:58 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GameLauncher.class.hpp>
#include <event.class.hpp>

void  Gamelauncher::campaign_new() {
  main_event->w_log("MENU_CAMPAIGN_NEW + LAUNCH ");
  main_event->draw_winner_multi = -1;
  main_event->draw_winner_campaign = -1;
  main_event->draw_lose_campaign = -1;
  main_event->draw_end_campaign = -1;
  main_event->actual_level = 1;
  main_event->coop = 0;
  main_event->multi = 0;
  main_event->arena = 0;
  // main_event->config[0] = PLAYER1; // player 1 get config number x
  main_event->mode_menu = false; // desactive menu render
  // if (main_event->game_playing == true) {
  main_event->make_new_game(0);
  // }
  main_event->game_playing = true; // activate active partie
}

void  Gamelauncher::campaign_new_coop() {
  main_event->w_log("MENU_CAMPAIGN_NEW_COOP + LAUNCH ");
  main_event->draw_winner_multi = -1;
  main_event->draw_winner_campaign = -1;
  main_event->draw_lose_campaign = -1;
  main_event->draw_end_campaign = -1;
  main_event->actual_level = 1;
  main_event->coop = 2;
  main_event->multi = 0;
  main_event->arena = 0;
  // main_event->config[0] = PLAYER1; // player 1 get config number x
  // main_event->config[1] = PLAYER2; // player 1 get config number x
  main_event->mode_menu = false; // desactive menu render
  // if (main_event->game_playing == true)
    main_event->make_new_game(0);
  main_event->game_playing = true; // activate active partie
}

void  Gamelauncher::run_multi_2() {
  main_event->w_log("MENU_MULTIPLAYER + MENU_MULTI_2P + LAUNCH ");
  main_event->draw_winner_multi = -1;
  main_event->draw_winner_campaign = -1;
  main_event->draw_lose_campaign = -1;
  main_event->draw_end_campaign = -1;
  main_event->coop = 0;
  main_event->multi = 2; // 2 players in game
  main_event->arena = 0;
  // main_event->config[0] = PLAYER1; // player 1 get config number x
  // main_event->config[1] = PLAYER2; // player 2 get config number x
  main_event->mode_menu = false; // desactive menu render
  // if (main_event->game_playing == true)
    main_event->make_new_game(0);
  main_event->game_playing = true; // activate active partie
}

void  Gamelauncher::run_multi_3() {
  main_event->w_log("MENU_MULTIPLAYER + MENU_MULTI_3P + LAUNCH ");
  main_event->draw_winner_multi = -1;
  main_event->draw_winner_campaign = -1;
  main_event->draw_lose_campaign = -1;
  main_event->draw_end_campaign = -1;
  main_event->coop = 0;
  main_event->multi = 3; // 3 players in game
  main_event->arena = 0;
  // main_event->config[0] = PLAYER1; // player 1 get config number x
  // main_event->config[1] = PLAYER2; // player 2 get config number x
  // main_event->config[2] = PLAYER3; // player 3 get config number x
  main_event->mode_menu = false; // desactive menu render
  // if (main_event->game_playing == true)
    main_event->make_new_game(0);
  main_event->game_playing = true; // activate active partie
}

void  Gamelauncher::run_multi_4() {
  main_event->w_log("MENU_MULTIPLAYER + MENU_MULTI_4P + LAUNCH ");
  main_event->draw_winner_multi = -1;
  main_event->draw_winner_campaign = -1;
  main_event->draw_lose_campaign = -1;
  main_event->draw_end_campaign = -1;
  main_event->coop = 0;
  main_event->multi = 4; // 4 players in game
  main_event->arena = 0;
  // main_event->config[0] = PLAYER1; // player 1 get config number x
  // main_event->config[1] = PLAYER2; // player 2 get config number x
  // main_event->config[2] = PLAYER3; // player 3 get config number x
  // main_event->config[3] = PLAYER4; // player 4 get config number x
  main_event->mode_menu = false; // desactive menu render
  // if (main_event->game_playing == true)
    main_event->make_new_game(0);
  main_event->game_playing = true; // activate active partie
}

void  Gamelauncher::run_multi_5() {
  main_event->w_log("MENU_MULTIPLAYER + MENU_MULTI_5P + LAUNCH ");
  main_event->draw_winner_multi = -1;
  main_event->draw_winner_campaign = -1;
  main_event->draw_lose_campaign = -1;
  main_event->draw_end_campaign = -1;
  main_event->coop = 0;
  main_event->multi = 5; // 4 players in game
  main_event->arena = 0;
  // main_event->config[0] = PLAYER1; // player 1 get config number x
  // main_event->config[1] = PLAYER2; // player 2 get config number x
  // main_event->config[2] = PLAYER3; // player 3 get config number x
  // main_event->config[3] = PLAYER4; // player 4 get config number x
  // main_event->config[4] = PLAYER5; // player 4 get config number x
  main_event->mode_menu = false; // desactive menu render
  // if (main_event->game_playing == true)
    main_event->make_new_game(0);
  main_event->game_playing = true; // activate active partie
}

void  Gamelauncher::run_arena_2() {
  main_event->w_log("MENU_MULTIPLAYER + MENU_ARENA_2P + LAUNCH ");
  main_event->draw_winner_multi = -1;
  main_event->draw_winner_campaign = -1;
  main_event->draw_lose_campaign = -1;
  main_event->draw_end_campaign = -1;
  main_event->coop = 0;
  main_event->multi = 0;
  main_event->arena = 2;  // 2 players in game
  // main_event->config[0] = PLAYER1; // player 1 get config number x
  // main_event->config[1] = PLAYER2; // player 2 get config number x
  main_event->mode_menu = false; // desactive menu render
  // if (main_event->game_playing == true)
    main_event->make_new_game(0);
  main_event->game_playing = true; // activate active partie
}

void  Gamelauncher::run_arena_3() {
  main_event->w_log("MENU_MULTIPLAYER + MENU_ARENA_3P + LAUNCH ");
  main_event->draw_winner_multi = -1;
  main_event->draw_winner_campaign = -1;
  main_event->draw_lose_campaign = -1;
  main_event->draw_end_campaign = -1;
  main_event->coop = 0;
  main_event->multi = 0;
  main_event->arena = 3;  // 3 players in game
  // main_event->config[0] = PLAYER1; // player 1 get config number x
  // main_event->config[1] = PLAYER2; // player 2 get config number x
  // main_event->config[2] = PLAYER3; // player 3 get config number x
  main_event->mode_menu = false; // desactive menu render
  // if (main_event->game_playing == true)
    main_event->make_new_game(0);
  main_event->game_playing = true; // activate active partie
}

void  Gamelauncher::run_arena_4() {
  main_event->w_log("MENU_MULTIPLAYER + MENU_ARENA_4P + LAUNCH ");
  main_event->draw_winner_multi = -1;
  main_event->draw_winner_campaign = -1;
  main_event->draw_lose_campaign = -1;
  main_event->draw_end_campaign = -1;
  main_event->coop = 0;
  main_event->multi = 0;
  main_event->arena = 4;  // 4 players in game
  // main_event->config[0] = PLAYER1; // player 1 get config number x
  // main_event->config[1] = PLAYER2; // player 2 get config number x
  // main_event->config[2] = PLAYER3; // player 3 get config number x
  // main_event->config[3] = PLAYER4; // player 4 get config number x
  main_event->mode_menu = false; // desactive menu render
  // if (main_event->game_playing == true)
    main_event->make_new_game(0);
  main_event->game_playing = true; // activate active partie
}

void  Gamelauncher::run_arena_5() {
  main_event->w_log("MENU_MULTIPLAYER + MENU_ARENA_5P + LAUNCH ");
  main_event->draw_winner_multi = -1;
  main_event->draw_winner_campaign = -1;
  main_event->draw_lose_campaign = -1;
  main_event->draw_end_campaign = -1;
  main_event->coop = 0;
  main_event->multi = 0;
  main_event->arena = 5;  // 4 players in game
  // main_event->config[0] = PLAYER1; // player 1 get config number x
  // main_event->config[1] = PLAYER2; // player 2 get config number x
  // main_event->config[2] = PLAYER3; // player 3 get config number x
  // main_event->config[3] = PLAYER4; // player 4 get config number x
  // main_event->config[4] = PLAYER5; // player 4 get config number x
  main_event->mode_menu = false; // desactive menu render
  // if (main_event->game_playing == true)
    main_event->make_new_game(0);
  main_event->game_playing = true; // activate active partie
}

Gamelauncher::Gamelauncher() {}

Gamelauncher::~Gamelauncher() {}
