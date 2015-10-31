#include <Menu.class.hpp>
#include <globject.class.hpp>
#include <event.class.hpp>

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
  if (NULL == this->ecran_menu) {
    SDL_FreeSurface(this->ecran_menu);
    this->ecran_menu = NULL;
  }
  this->ecran_menu = SDL_CreateRGBSurface(0, 1300, 1300, 32, 0, 0, 0, 0);
  if (NULL == this->ecran_menu) {
    this->w_full("Menu::big_menu ecran_menu allocation error");
    throw std::exception();
  }

  glClear((GL_COLOR_BUFFER_BIT)| GL_DEPTH_BUFFER_BIT);
  SDL_FillRect(this->ecran_menu, NULL, SDL_MapRGB(this->ecran_menu->format, 0, 0, 0) );

  this->position.x = 400;
  this->position.y = 400;
  SDL_BlitSurface(this->str_campaign, NULL, this->ecran_menu, &this->position);

  this->position.x = 400;
  this->position.y = 500;
  SDL_BlitSurface(this->str_arena, NULL, this->ecran_menu, &this->position);

  this->position.x = 400;
  this->position.y = 600;
  SDL_BlitSurface(this->str_multiplayer, NULL, this->ecran_menu, &this->position);

  this->position.x = 400;
  this->position.y = 700;
  SDL_BlitSurface(this->str_exit, NULL, this->ecran_menu, &this->position);

  globject::display_menu(this->ecran_menu);
  SDL_GL_SwapWindow(globject::_displayWindow);
}

// https://openclassrooms.com/courses/apprenez-a-programmer-en-c/ecrire-du-texte-avec-sdl-ttf

void Menu::init() {
  this->SansPosterBold = TTF_OpenFont("src/menu/fonts/SansPosterBold.ttf", 24);
  this->white = {255, 255, 255, 1};
  this->blue = {0, 0, 255, 1};
  this->red = {255, 0, 0, 1};

  this->str_campaign = TTF_RenderText_Blended(this->SansPosterBold, "Campain", this->white);
  this->str_campaign_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Campain <<", this->white);
  this->str_campaign_new = TTF_RenderText_Blended(this->SansPosterBold, "New", this->white);
  this->str_campaign_new_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> New <<", this->white);
  this->str_campaign_coop = TTF_RenderText_Blended(this->SansPosterBold, "Coop", this->white);
  this->str_campaign_coop_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Coop <<", this->white);
  this->str_campaign_continue = TTF_RenderText_Blended(this->SansPosterBold, "Continue", this->white);
  this->str_campaign_continue_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Continue <<", this->white);
  this->str_arena = TTF_RenderText_Blended(this->SansPosterBold, "Arena", this->white);
  this->str_arena_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Arena", this->white);
  this->str_2players = TTF_RenderText_Blended(this->SansPosterBold, "2 Players", this->white);
  this->str_2players_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> 2 Players <<", this->white);
  this->str_3players = TTF_RenderText_Blended(this->SansPosterBold, "3 Players", this->white);
  this->str_3players_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> 3 Players <<", this->white);
  this->str_4players = TTF_RenderText_Blended(this->SansPosterBold, "4 Players", this->white);
  this->str_4players_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> 4 Players <<", this->white);
  this->str_5players = TTF_RenderText_Blended(this->SansPosterBold, "5 Players", this->white);
  this->str_5players_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> 5 Players <<", this->white);
  this->str_multiplayer = TTF_RenderText_Blended(this->SansPosterBold, "Multi Players", this->white);
  this->str_multiplayer_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Multi Players <<", this->white);
  this->str_exit = TTF_RenderText_Blended(this->SansPosterBold, "Exit Game", this->white);
  this->str_exit_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Exit Game <<", this->white);
  this->str_exit_confirm = TTF_RenderText_Blended(this->SansPosterBold, "Confirm exit game ?", this->white);
  this->str_exit_yes = TTF_RenderText_Blended(this->SansPosterBold, "Yes", this->white);
  this->str_exit_yes_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Yes <<", this->white);
  this->str_exit_no = TTF_RenderText_Blended(this->SansPosterBold, "No", this->white);
  this->str_exit_no_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> No <<", this->white);
}

void Menu::intro_start() {
  if (false == this->introstart) {
    glClear((GL_COLOR_BUFFER_BIT)| GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);
    if (NULL == this->ecran_menu)
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
