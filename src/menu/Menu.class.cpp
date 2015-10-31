#include <Menu.class.hpp>
#include <globject.class.hpp>
#include <event.class.hpp>
#include <SDL_ttf.h>

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

void  Menu::big_menu() {
  glClear((GL_COLOR_BUFFER_BIT)| GL_DEPTH_BUFFER_BIT);


  SDL_Color White = {255, 255, 255, 1};
  TTF_Font * fontest = TTF_OpenFont("src/menu/fonts/SansPosterBold.ttf", 24);

  SDL_Surface* surfaceMessage = TTF_RenderText_Blended(fontest, "put your text here", White);


  // SDL_Flip(surfaceMessage);
  globject::display_menu(surfaceMessage);
  SDL_GL_SwapWindow(globject::_displayWindow);
}

// https://openclassrooms.com/courses/apprenez-a-programmer-en-c/ecrire-du-texte-avec-sdl-ttf

void Menu::init() {
  this->SansPosterBold = TTF_OpenFont("src/menu/fonts/SansPosterBold.ttf", 24);
}

void Menu::intro_start() {
  if (false == this->introstart) {
    glClear((GL_COLOR_BUFFER_BIT)| GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);
    if (NULL == this->current)
      SDL_FreeSurface(this->current);
    this->current = NULL;
    this->current = IMG_Load("src/menu/assets/intro_start-2.bmp");
    if (NULL == this->current) {
      std::cerr << "Menu::intro_start load image error " << SDL_GetError() << std::endl;
      throw std::exception();
    }
    globject::display_menu(this->current);
    SDL_GL_SwapWindow(globject::_displayWindow);
  }
}

void  Menu::main_loop() {
  std::cout << "deb 0" << std::endl;
  while (true == main_event->mode_menu) {
    if (false == this->introstart)
      this->intro_start();
    else
      this->big_menu();
    this->menu_keyboard();
    usleep(5000);
  }
  std::cout << "deb 1" << std::endl;

}

void  Menu::menu_keyboard(void) {
	  SDL_Event           event;

  	while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            switch((event).key.keysym.sym) {
          			case SDLK_ESCAPE:     _exit(0); break;

                case SDLK_SPACE:     if (false == this->introstart) {
                                        this->introstart = true;
                                        main_event->mode_menu = false;
                                      }
                                      break;

          			// case SDLK_DOWN:     key.key_up = 1; break;
          			// case SDLK_UP:       key.key_down = 1; break;
          			// case SDLK_RIGHT:    key.key_right = 1; break;
          			// case SDLK_LEFT:     key.key_left = 1; break;
          			// case SDLK_KP_0:    	main_event->player_bomb(PLAYER1); break;
          			// case SDLK_s:     		key2.key_up = 1; break;
          			// case SDLK_w:       	key2.key_down = 1; break;
          			// case SDLK_d:    		key2.key_right = 1; break;
          			// case SDLK_a:     		key2.key_left = 1; break;
          			// case SDLK_SPACE:    main_event->player_bomb(PLAYER2); break;

          			case SDLK_p:        if (true == main_event->mode_menu)
          														main_event->mode_menu = false;
          													else
          														main_event->mode_menu = true;
          													break;

          			default: break;
    			  }
        }
    }
}

Menu::Menu(Event * event) : event(event), current(NULL) {}

Menu::~Menu() {}
