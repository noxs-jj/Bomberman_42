#include <Menu.class.hpp>
#include <globject.class.hpp>
#include <event.class.hpp>

void  Menu::campaign() {
  print_surface(this->str_campaign_new, this->str_campaign_new_selected, 400, 400, MENU_CAMPAIGN_NEW);
  print_surface(this->str_campaign_continue, this->str_campaign_continue_selected, 400, 500, MENU_CAMPAIGN_CONTINUE);
  print_surface(this->str_campaign_coop, this->str_campaign_coop_selected, 400, 600, MENU_CAMPAIGN_COOP);
  print_surface(this->str_return, this->str_return_selected, 400, 700, MENU_CAMPAIGN_RETURN);
}



void  Menu::multi_2players() {}

void  Menu::multi_3players() {}

void  Menu::multi_4players() {}

void  Menu::config() {
  print_surface(this->str_campaign_new, this->str_campaign_new_selected, 400, 400, MENU_CONFIG_NAME);
  print_surface(this->str_campaign_new, this->str_campaign_new_selected, 400, 500, MENU_CONFIG_NAMEA);
  print_surface(this->str_campaign_new, this->str_campaign_new_selected, 400, 600, MENU_CONFIG_NAMEB);
  print_surface(this->str_return, this->str_return_selected, 400, 700, MENU_CONFIG_RETURN);
}

void  Menu::exit_game() {}

void  Menu::exit_confirm() {}

void  Menu::print_surface(SDL_Surface * str, SDL_Surface * str_select, int x, int y, int type) {
  this->position.x = x;
  this->position.y = y;
  if (type == this->detail_menu_selected)
    SDL_BlitSurface(str_select, NULL, this->ecran_menu, &this->position);
  else
    SDL_BlitSurface(str, NULL, this->ecran_menu, &this->position);
}

void  Menu::big_menu() {
  print_surface(this->str_campaign, this->str_campaign_selected, 400, 400, MENU_CAMPAIGN);
  print_surface(this->str_arena, this->str_arena_selected, 400, 500, MENU_ARENA);
  print_surface(this->str_multiplayer, this->str_multiplayer_selected, 400, 600, MENU_MULTIPLAYER);
  print_surface(this->str_config, str_config_selected, 400, 700, MENU_CONFIG);
  print_surface(this->str_exit, this->str_exit_selected, 400, 800, MENU_EXIT);
}

// https://openclassrooms.com/courses/apprenez-a-programmer-en-c/ecrire-du-texte-avec-sdl-ttf

void Menu::init() {
  this->SansPosterBold = TTF_OpenFont("src/menu/fonts/SansPosterBold.ttf", 24);
  this->white = {255, 255, 255, 1};
  this->blue = {0, 0, 255, 1};
  this->red = {255, 0, 0, 1};

  this->menu_selected = BIG_MENU;
  this->detail_menu_selected = MENU_CAMPAIGN;
  this->str_campaign = TTF_RenderText_Blended(this->SansPosterBold, "Campaign", this->white);
  this->str_campaign_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Campaign <<", this->white);
  this->str_campaign_new = TTF_RenderText_Blended(this->SansPosterBold, "New", this->white);
  this->str_campaign_new_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> New <<", this->white);
  this->str_campaign_coop = TTF_RenderText_Blended(this->SansPosterBold, "Coop", this->white);
  this->str_campaign_coop_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Coop <<", this->white);
  this->str_campaign_continue = TTF_RenderText_Blended(this->SansPosterBold, "Continue", this->white);
  this->str_campaign_continue_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Continue <<", this->white);
  this->str_arena = TTF_RenderText_Blended(this->SansPosterBold, "Arena", this->white);
  this->str_arena_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Arena <<", this->white);
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
  this->str_config = TTF_RenderText_Blended(this->SansPosterBold, "Config", this->white);
  this->str_config_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Config <<", this->white);
  this->str_exit = TTF_RenderText_Blended(this->SansPosterBold, "Exit Game", this->white);
  this->str_exit_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Exit Game <<", this->white);
  this->str_exit_confirm = TTF_RenderText_Blended(this->SansPosterBold, "Confirm exit game ?", this->white);
  this->str_exit_yes = TTF_RenderText_Blended(this->SansPosterBold, "Yes", this->white);
  this->str_exit_yes_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Yes <<", this->white);
  this->str_exit_no = TTF_RenderText_Blended(this->SansPosterBold, "No", this->white);
  this->str_exit_no_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> No <<", this->white);
  this->str_return = TTF_RenderText_Blended(this->SansPosterBold, "Return", this->white);
  this->str_return_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Return <<", this->white);

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

void  Menu::menu_selection() {
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

  switch(this->menu_selected) {
    case BIG_MENU: this->big_menu(); break;
    case CAMPAIGN: this->campaign(); break;
    case CONFIG: this->config(); break;
  }

  globject::display_menu(this->ecran_menu);
  SDL_GL_SwapWindow(globject::_displayWindow);
}

void  Menu::main_loop() {
  std::cout << "deb 0" << std::endl;
  while (true == main_event->mode_menu) {
    if (false == this->introstart)
      this->intro_start();
    else
      this->menu_selection();
    this->menu_keyboard();
    usleep(5000);
  }
  std::cout << "deb 1" << std::endl;

}

void  Menu::move_menu_ver(int dir) {
  if (this->menu_selected == BIG_MENU) {
    if (dir == -1 && this->detail_menu_selected == MENU_CAMPAIGN) {
      this->detail_menu_selected = MENU_EXIT;
    }
    else if (dir == 1 && this->detail_menu_selected == MENU_EXIT) {
      this->detail_menu_selected = MENU_CAMPAIGN;
    }
    else
     this->detail_menu_selected += dir;
  }
  else if (this->menu_selected == CAMPAIGN) {
    if (dir == -1 && this->detail_menu_selected == MENU_CAMPAIGN_NEW) {
      this->detail_menu_selected = MENU_CAMPAIGN_RETURN;
    }
    else if (dir == 1 && this->detail_menu_selected == MENU_CAMPAIGN_RETURN) {
      this->detail_menu_selected = MENU_CAMPAIGN_NEW;
    }
    else
     this->detail_menu_selected += dir;
  }
  else if (this->menu_selected == CONFIG) {
    if (dir == -1 && this->detail_menu_selected == MENU_CONFIG_NAME) {
      this->detail_menu_selected = MENU_CONFIG_RETURN;
    }
    else if (dir == 1 && this->detail_menu_selected == MENU_CONFIG_RETURN) {
      this->detail_menu_selected = MENU_CONFIG_NAME;
    }
    else
     this->detail_menu_selected += dir;
  }
}

void  Menu::change_menu() {
  if (this->detail_menu_selected == MENU_CAMPAIGN) {
    this->detail_menu_selected = MENU_CAMPAIGN_NEW;
    this->menu_selected = CAMPAIGN;
  }
  else if (this->detail_menu_selected == MENU_CONFIG) {
    this->detail_menu_selected = MENU_CONFIG_NAME;
    this->menu_selected = CONFIG;
  }
  else if (this->detail_menu_selected == MENU_CAMPAIGN_RETURN || this->detail_menu_selected == MENU_CONFIG_RETURN) {
    this->detail_menu_selected = MENU_CAMPAIGN;
    this->menu_selected = BIG_MENU;
  }


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
    case SDLK_DOWN:     move_menu_ver(1); break;
    case SDLK_UP:       move_menu_ver(-1); break;
    case SDLK_RIGHT:    std::cout << "hey" << std::endl; break;
    case SDLK_LEFT:     std::cout << "hey" << std::endl; break;
    case SDLK_RETURN:   change_menu(); break;

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
