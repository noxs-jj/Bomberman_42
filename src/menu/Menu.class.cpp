#include <Menu.class.hpp>
#include <globject.class.hpp>
#include <event.class.hpp>
#include <GameLauncher.class.hpp>
#include <soundrender.class.hpp>

void  Menu::campaign() {
  print_surface(this->str_campaign_new, this->str_campaign_new_selected, 400, 400, MENU_CAMPAIGN_NEW);
  print_surface(this->str_campaign_continue, this->str_campaign_continue_selected, 400, 500, MENU_CAMPAIGN_CONTINUE);
  print_surface(this->str_campaign_coop, this->str_campaign_coop_selected, 400, 600, MENU_CAMPAIGN_COOP);
  print_surface(this->str_return, this->str_return_selected, 400, 700, MENU_CAMPAIGN_RETURN);
}

void  Menu::arena() {
  print_surface(this->str_2players, this->str_2players_selected, 400, 400, MENU_ARENA_2P);
  print_surface(this->str_3players, this->str_3players_selected, 400, 500, MENU_ARENA_3P);
  print_surface(this->str_4players, this->str_4players_selected, 400, 600, MENU_ARENA_4P);
  print_surface(this->str_return, this->str_return_selected, 400, 700, MENU_ARENA_RETURN);
}

void  Menu::multiplayer() {
  print_surface(this->str_2players, this->str_2players_selected, 400, 400, MENU_MULTI_2P);
  print_surface(this->str_3players, this->str_3players_selected, 400, 500, MENU_MULTI_3P);
  print_surface(this->str_4players, this->str_4players_selected, 400, 600, MENU_MULTI_4P);
  print_surface(this->str_return, this->str_return_selected, 400, 700, MENU_MULTI_RETURN);
}

void  Menu::config() {
  print_surface(this->str_campaign_new, this->str_campaign_new_selected, 400, 400, MENU_CONFIG_NAME);
  print_surface(this->str_campaign_new, this->str_campaign_new_selected, 400, 500, MENU_CONFIG_NAMEA);
  print_surface(this->str_campaign_new, this->str_campaign_new_selected, 400, 600, MENU_CONFIG_NAMEB);
  print_surface(this->str_return, this->str_return_selected, 400, 700, MENU_CONFIG_RETURN);
}

void  Menu::exit_game() {
  print_surface(this->str_exit_confirm, this->str_exit_confirm_selected, 400, 400, MENU_EXIT_CONFIRM);
  print_surface(this->str_return, this->str_return_selected, 400, 500, MENU_EXIT_RETURN);
}

void  Menu::print_surface(SDL_Surface * str, SDL_Surface * str_select, int x, int y, int type) {
  this->position.x = x;
  this->position.y = y;
  if (type == this->detail_menu_selected)
    SDL_BlitSurface(str_select, NULL, this->ecran_menu, &this->position);
  else
    SDL_BlitSurface(str, NULL, this->ecran_menu, &this->position);
}

void  Menu::big_menu() {
  if (true == main_event->game_playing) // Si partie en cours
    print_surface(this->str_resume_game, this->str_resume_game_selected, 400, 300, RESUME_GAME);
  print_surface(this->str_campaign, this->str_campaign_selected, 400, 400, MENU_CAMPAIGN);
  print_surface(this->str_arena, this->str_arena_selected, 400, 500, MENU_ARENA);
  print_surface(this->str_multiplayer, this->str_multiplayer_selected, 400, 600, MENU_MULTIPLAYER);
  print_surface(this->str_config, str_config_selected, 400, 700, MENU_CONFIG);
  print_surface(this->str_exit, this->str_exit_selected, 400, 800, MENU_EXIT);
}

void Menu::init() {
  this->SansPosterBold = TTF_OpenFont("src/menu/fonts/SansPosterBold.ttf", 24);
  this->white = {255, 255, 255, 1};
  this->blue = {0, 0, 255, 1};
  this->red = {255, 0, 0, 1};
  SDL_JoystickEventState(SDL_ENABLE);
  this->manette1 = SDL_GameControllerOpen(0);
  if (this->manette1 < NULL) {
    std::cerr << "Could not open gamecontroller " << SDL_GetError() << std::endl;
    throw std::exception();
  }

  this->menu_selected = BIG_MENU;
  this->detail_menu_selected = MENU_CAMPAIGN;
  this->str_resume_game = TTF_RenderText_Blended(this->SansPosterBold, "Resume Game", this->white);
  this->str_resume_game_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Resume Game <<", this->red);
  this->str_campaign = TTF_RenderText_Blended(this->SansPosterBold, "Campaign", this->white);
  this->str_campaign_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Campaign <<", this->red);
  this->str_campaign_new = TTF_RenderText_Blended(this->SansPosterBold, "New", this->white);
  this->str_campaign_new_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> New <<", this->red);
  this->str_campaign_coop = TTF_RenderText_Blended(this->SansPosterBold, "Coop", this->white);
  this->str_campaign_coop_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Coop <<", this->red);
  this->str_campaign_continue = TTF_RenderText_Blended(this->SansPosterBold, "Continue", this->white);
  this->str_campaign_continue_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Continue <<", this->red);
  this->str_arena = TTF_RenderText_Blended(this->SansPosterBold, "Arena", this->white);
  this->str_arena_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Arena <<", this->red);
  this->str_2players = TTF_RenderText_Blended(this->SansPosterBold, "2 Players", this->white);
  this->str_2players_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> 2 Players <<", this->red);
  this->str_3players = TTF_RenderText_Blended(this->SansPosterBold, "3 Players", this->white);
  this->str_3players_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> 3 Players <<", this->red);
  this->str_4players = TTF_RenderText_Blended(this->SansPosterBold, "4 Players", this->white);
  this->str_4players_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> 4 Players <<", this->red);
  this->str_5players = TTF_RenderText_Blended(this->SansPosterBold, "5 Players", this->white);
  this->str_5players_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> 5 Players <<", this->red);
  this->str_multiplayer = TTF_RenderText_Blended(this->SansPosterBold, "Multi Players", this->white);
  this->str_multiplayer_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Multi Players <<", this->red);
  this->str_config = TTF_RenderText_Blended(this->SansPosterBold, "Config", this->white);
  this->str_config_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Config <<", this->red);
  this->str_exit = TTF_RenderText_Blended(this->SansPosterBold, "Exit Game", this->white);
  this->str_exit_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Exit Game <<", this->red);
  this->str_exit_confirm = TTF_RenderText_Blended(this->SansPosterBold, "Confirm exit game", this->white);
  this->str_exit_confirm_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Confirm exit game <<", this->red);
  this->str_return = TTF_RenderText_Blended(this->SansPosterBold, "Return", this->white);
  this->str_return_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Return <<", this->red);

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
    case ARENA: this->arena(); break;
    case MULTIPLAYER: this->multiplayer(); break;
    case CONFIG: this->config(); break;
    case EXIT: this->exit_game(); break;
  }

  globject::display_menu(this->ecran_menu);
  SDL_GL_SwapWindow(globject::_displayWindow);
}

void  Menu::main_loop() {
  while (true == main_event->mode_menu) {
    if (false == this->introstart)
      this->intro_start();
    else
      this->menu_selection();
    this->menu_keyboard();
    usleep(5000);
  }
}

void  Menu::move_menu_ver(int dir) {
  main_event->soundrender->playSound("menu1");
  if (this->menu_selected == BIG_MENU) {
    if (dir == -1 && main_event->game_playing == true && this->detail_menu_selected == RESUME_GAME) {
      this->detail_menu_selected = MENU_EXIT;
    }
    else if (dir == 1 && main_event->game_playing == false && this->detail_menu_selected == MENU_CAMPAIGN) {
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

  else if (this->menu_selected == ARENA) {
    if (dir == -1 && this->detail_menu_selected == MENU_ARENA_2P) {
      this->detail_menu_selected = MENU_ARENA_RETURN;
    }
    else if (dir == 1 && this->detail_menu_selected == MENU_ARENA_RETURN) {
      this->detail_menu_selected = MENU_ARENA_2P;
    }
    else
     this->detail_menu_selected += dir;
  }


  else if (this->menu_selected == MULTIPLAYER) {
    if (dir == -1 && this->detail_menu_selected == MENU_MULTI_2P) {
      this->detail_menu_selected = MENU_MULTI_RETURN;
    }
    else if (dir == 1 && this->detail_menu_selected == MENU_MULTI_RETURN) {
      this->detail_menu_selected = MENU_MULTI_2P;
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


  else if (this->menu_selected == EXIT) {
    if (this->detail_menu_selected == MENU_EXIT_CONFIRM) {
      this->detail_menu_selected = MENU_EXIT_RETURN;
    }
    else if (this->detail_menu_selected == MENU_EXIT_RETURN) {
      this->detail_menu_selected = MENU_EXIT_CONFIRM;
    }
  }
}

void  Menu::change_menu() {
  main_event->soundrender->playSound("menu2");
  if ( false == main_event->game_playing && CAMPAIGN == this->menu_selected && MENU_CAMPAIGN_NEW == this->detail_menu_selected )
    Gamelauncher::campaign_new();
  else if (this->detail_menu_selected == MENU_CAMPAIGN) {
    this->detail_menu_selected = MENU_CAMPAIGN_NEW;
    this->menu_selected = CAMPAIGN;
  }


  else if (this->detail_menu_selected == MENU_CONFIG) {
    this->detail_menu_selected = MENU_CONFIG_NAME;
    this->menu_selected = CONFIG;
  }

  else if ( false == main_event->game_playing && this->menu_selected == MULTIPLAYER && this->detail_menu_selected == MENU_MULTI_4P )
    Gamelauncher::run_multi_4(); // Multiplayer 4 Players Launcher game
  else if ( false == main_event->game_playing && this->menu_selected == MULTIPLAYER && this->detail_menu_selected == MENU_MULTI_3P )
    Gamelauncher::run_multi_3(); // Multiplayer 3 Players Launcher game
  else if ( false == main_event->game_playing && this->menu_selected == MULTIPLAYER && this->detail_menu_selected == MENU_MULTI_2P )
    Gamelauncher::run_multi_2(); // Multiplayer 2 Players Launcher game
  else if (this->detail_menu_selected == MENU_MULTIPLAYER) {
    this->detail_menu_selected = MENU_MULTI_2P;
    this->menu_selected = MULTIPLAYER;
  }

  else if ( false == main_event->game_playing && this->menu_selected == ARENA && this->detail_menu_selected == MENU_ARENA_4P )
    Gamelauncher::run_arena_4();
  else if ( false == main_event->game_playing && this->menu_selected == ARENA && this->detail_menu_selected == MENU_ARENA_3P )
    Gamelauncher::run_arena_3();
  else if ( false == main_event->game_playing && this->menu_selected == ARENA && this->detail_menu_selected == MENU_ARENA_2P )
    Gamelauncher::run_arena_2();
  else if (this->detail_menu_selected == MENU_ARENA) {
    this->detail_menu_selected = MENU_ARENA_2P;
    this->menu_selected = ARENA;
  }

  else if (this->detail_menu_selected == MENU_CAMPAIGN_RETURN
    || this->detail_menu_selected == MENU_CONFIG_RETURN
    || this->detail_menu_selected == MENU_EXIT_RETURN
    || this->detail_menu_selected == MENU_ARENA_RETURN
    || this->detail_menu_selected == MENU_MULTI_RETURN) {
    this->detail_menu_selected = MENU_CAMPAIGN;
    this->menu_selected = BIG_MENU;
  }

  else if (this->detail_menu_selected == MENU_EXIT) {
    this->detail_menu_selected = MENU_EXIT_CONFIRM;
    this->menu_selected = EXIT;
  }

  else if (this->detail_menu_selected == MENU_EXIT_CONFIRM)
    _exit(0);
}

void  Menu::menu_keyboard(void) {
  SDL_Event           event;
  int i = 0;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_KEYDOWN) {
      std::cout << "(event).key.keysym.sym " << (event).key.keysym.sym << std::endl;
      switch((event).key.keysym.sym) {
        case SDLK_ESCAPE:     _exit(0); break;

        case SDLK_SPACE:    if (false == this->introstart) {
          this->introstart = true;
          main_event->mode_menu = true;
        }
        break;

        case SDLK_DOWN:     move_menu_ver(1); break;
        case SDLK_UP:       move_menu_ver(-1); break;
        case SDLK_RIGHT:    std::cout << "hey" << std::endl; break;
        case SDLK_LEFT:     std::cout << "hey" << std::endl; break;
        case SDLK_RETURN:   change_menu(); break;


        case SDLK_p:        if (true == main_event->mode_menu)
        main_event->mode_menu = false;
        else
        main_event->mode_menu = true;
        break;

        case SDLK_c:        std::cout << "SDL_NumJoysticks(void) " << SDL_NumJoysticks() << std::endl;
        while ( i < SDL_NumJoysticks() ){
          printf("    %s\n", SDL_GameControllerNameForIndex(i) );
          i++;
        }
        break;

        default: break;
      }
    }
    else if (event.type == SDL_CONTROLLERBUTTONDOWN) {
      fprintf(stdout, "Appui bouton joystick :\n");
      fprintf(stdout, "\tjoystick : %d\n",event.jbutton.which);
      fprintf(stdout, "\tbutton : %d\n",event.jbutton.button);
      fprintf(stdout, "\tétat : %d\n",event.jbutton.state);
      switch (event.cbutton.button) {
        case SDL_CONTROLLER_BUTTON_A             : change_menu(); break;
        case SDL_CONTROLLER_BUTTON_B             : (void)0; break;
        case SDL_CONTROLLER_BUTTON_X             : (void)0; break;
        case SDL_CONTROLLER_BUTTON_Y             : (void)0; break;
        case SDL_CONTROLLER_BUTTON_BACK          : (void)0; break;
        case SDL_CONTROLLER_BUTTON_GUIDE         : (void)0; break;
        case SDL_CONTROLLER_BUTTON_START         : (void)0; break;
        case SDL_CONTROLLER_BUTTON_LEFTSTICK     : (void)0; break;
        case SDL_CONTROLLER_BUTTON_RIGHTSTICK    : (void)0; break;
        case SDL_CONTROLLER_BUTTON_LEFTSHOULDER  : (void)0; break;
        case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER : (void)0; break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP       : move_menu_ver(-1); break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN     : move_menu_ver(1); break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT     : (void)0; break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT    : (void)0; break;
        case SDL_CONTROLLER_BUTTON_MAX           : (void)0; break;
        default: break;
      }
    }
  }
}

Menu::Menu(Event * event) : event(event), current(NULL) {}

Menu::~Menu() {}
