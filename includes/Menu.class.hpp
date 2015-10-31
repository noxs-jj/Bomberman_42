#ifndef MENU_CLASS_HPP
# define MENU_CLASS_HPP

# include <ft42.class.hpp>

class Event;

class Menu : public ft42 {
public:

  Event *         event;
  SDL_Surface *   current;
  SDL_Surface *   ecran_menu;
  bool            introstart;
  TTF_Font *      SansPosterBold;

  SDL_Color       white;
  SDL_Color       blue;
  SDL_Color       red;
  SDL_Rect        position;

  SDL_Surface *   str_return;
  SDL_Surface *   str_return_selected;
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
  SDL_Surface *   str_exit;
  SDL_Surface *   str_exit_selected;
  SDL_Surface *   str_exit_confirm;
  SDL_Surface *   str_exit_yes;
  SDL_Surface *   str_exit_yes_selected;
  SDL_Surface *   str_exit_no;
  SDL_Surface *   str_exit_no_selected;





  Menu(Event * event);
  virtual ~Menu();

  void            campain_new_game();
  void            campain_coop();
  void            campain_continue();
  void            option_video();
  void            option_sound();
  void            option_keybinding();
  void            multi_2players();
  void            multi_3players();
  void            multi_4players();
  void            exit_game();
  void            exit_confirm();
  void            intro_start() ;
  void            main_loop();
  void            menu_keyboard();
  void            big_menu();
  void            init();

private:
  Menu( void );
};

#endif
