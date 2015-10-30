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
  this->current = SDL_LoadBMP("src/menu/assets/intro_start.bmp");
  // this->current = IMG_LoadPNG_RW("src/menu/assets/intro_start.bmp");
  if (NULL == this->current) {

    std::cerr << "Menu::intro_start load image error " << SDL_GetError() << std::endl;
    throw std::exception();
  }
}


Menu::Menu(Event * event) : event(event), current(NULL) {}

Menu::~Menu() {}
