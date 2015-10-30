#include <Menu.class.hpp>

void  Menu::campain_new_game() {}

void  Menu::campain_coop() {}

void  Menu::campain_continue() {}

void  Menu::option_video() {}

void  Menu::option_sound() {}

void  Menu::option_keybinding() {}

void  Menu::multi_2players() {}

void  Menu::multi_3players() {}

void  Menu::multi_4players() {}

void  Menu::exit_game() {}

void  Menu::exit_confirm() {}

void Menu::intro_start() {
  this->current = NULL;
  this->current = SDL_LoadBMP("src/menu/assets/42test.bmp");
  std::cerr << "img 0" << std::endl;
  if (NULL == this->current) {
    std::cerr << "img 1" << std::endl;
    this->w_full("Menu::intro_start load image error");
    throw std::exception();
  }
  std::cerr << "img 2" << std::endl;
}


Menu::Menu(Event * event) : event(event), current(NULL) {}

Menu::~Menu() {}
