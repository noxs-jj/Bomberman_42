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

Menu::Menu(Event & event) : event(event) {}

Menu::~Menu() {}
