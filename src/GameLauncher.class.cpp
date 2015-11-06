#include <GameLauncher.class.hpp>
#include <event.class.hpp>

void  Gamelauncher::campaign_new() {
  main_event->w_log("MENU_CAMPAIGN_NEW + LAUNCH ");
  main_event->coop = 0;
  main_event->multi = 0;
  main_event->arena = 0;
  main_event->config[0] = 0x0; // player 1 get config number x
  main_event->mode_menu = false; // desactive menu render
  main_event->game_playing = true; // activate active partie
}

void  Gamelauncher::run_multi_2() {
  main_event->w_log("MENU_MULTIPLAYER + MENU_MULTI_2P + LAUNCH ");
  main_event->coop = 0;
  main_event->multi = 2; // 2 players in game
  main_event->arena = 0;
  main_event->config[0] = 0x0; // player 1 get config number x
  main_event->config[1] = 0x0; // player 2 get config number x
  main_event->mode_menu = false; // desactive menu render
  main_event->game_playing = true; // activate active partie
}

void  Gamelauncher::run_multi_3() {
  main_event->w_log("MENU_MULTIPLAYER + MENU_MULTI_3P + LAUNCH ");
  main_event->coop = 0;
  main_event->multi = 3; // 3 players in game
  main_event->arena = 0;
  main_event->config[0] = 0x0; // player 1 get config number x
  main_event->config[1] = 0x0; // player 2 get config number x
  main_event->config[2] = 0x0; // player 3 get config number x
  main_event->mode_menu = false; // desactive menu render
  main_event->game_playing = true; // activate active partie
}

void  Gamelauncher::run_multi_4() {
  main_event->w_log("MENU_MULTIPLAYER + MENU_MULTI_4P + LAUNCH ");
  main_event->coop = 0;
  main_event->multi = 4; // 4 players in game
  main_event->arena = 0;
  main_event->config[0] = 0x0; // player 1 get config number x
  main_event->config[1] = 0x0; // player 2 get config number x
  main_event->config[2] = 0x0; // player 3 get config number x
  main_event->config[3] = 0x0; // player 4 get config number x
  main_event->mode_menu = false; // desactive menu render
  main_event->game_playing = true; // activate active partie
}

void  Gamelauncher::run_arena_2() {
  main_event->w_log("MENU_MULTIPLAYER + MENU_ARENA_2P + LAUNCH ");
  main_event->coop = 0;
  main_event->multi = 0;
  main_event->arena = 2;  // 2 players in game
  main_event->config[0] = 0x0; // player 1 get config number x
  main_event->config[1] = 0x0; // player 2 get config number x
  main_event->mode_menu = false; // desactive menu render
  main_event->game_playing = true; // activate active partie
}

void  Gamelauncher::run_arena_3() {
  main_event->w_log("MENU_MULTIPLAYER + MENU_ARENA_3P + LAUNCH ");
  main_event->coop = 0;
  main_event->multi = 0;
  main_event->arena = 3;  // 3 players in game
  main_event->config[0] = 0x0; // player 1 get config number x
  main_event->config[1] = 0x0; // player 2 get config number x
  main_event->config[2] = 0x0; // player 3 get config number x
  main_event->config[3] = 0x0; // player 4 get config number x
  main_event->mode_menu = false; // desactive menu render
  main_event->game_playing = true; // activate active partie
}

void  Gamelauncher::run_arena_4() {
  main_event->w_log("MENU_MULTIPLAYER + MENU_ARENA_4P + LAUNCH ");
  main_event->coop = 0;
  main_event->multi = 0;
  main_event->arena = 4;  // 4 players in game
  main_event->config[0] = 0x0; // player 1 get config number x
  main_event->config[1] = 0x0; // player 2 get config number x
  main_event->config[2] = 0x0; // player 3 get config number x
  main_event->config[3] = 0x0; // player 4 get config number x
  main_event->mode_menu = false; // desactive menu render
  main_event->game_playing = true; // activate active partie
}


Gamelauncher::Gamelauncher() {}

Gamelauncher::~Gamelauncher() {}
