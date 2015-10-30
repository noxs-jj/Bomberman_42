#ifndef MENU_CLASS_HPP
# define MENU_CLASS_HPP

# include <ft42.class.hpp>

class Event;

class Menu : public ft42 {
public:

  Event *         event;
  SDL_Surface *   current;

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
  void            intro_start();

private:
  Menu( void );
};

#endif
