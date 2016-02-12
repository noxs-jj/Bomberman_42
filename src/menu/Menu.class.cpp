// ************************************************************************** //
//   24 Bomb                                                                  //
//   By: rcargou <rcargou@student.42.fr>                  :::      ::::::::   //
//   By: nmohamed <nmohamed@student.42.fr>              :+:      :+:    :+:   //
//   By: adjivas <adjivas@student.42.fr>              +:+ +:+         +:+     //
//   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        //
//   By: jmoiroux <jmoiroux@student.42.fr>        +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 17:03:20 by rcargou           #+#    #+#             //
//   Updated: 2015/10/27 14:00:02 by rcargou          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <Menu.class.hpp>
#include <globject.class.hpp>
#include <event.class.hpp>
#include <GameLauncher.class.hpp>
#include <soundrender.class.hpp>
#include <joystick.hpp>

void	Menu::winner_multi() {
	if (!this->musicIsPlaying)
	{
		this->musicIsPlaying = true;
		main_event->soundrender->playMusic("victory_multiplayer");
	}
	// std::cout << "main_event->winner_multi " << main_event->draw_winner_multi << std::endl;
	print_surface(this->winner[main_event->draw_winner_multi - 1], this->winner[main_event->draw_winner_multi - 1], 400, 400, 0);
}

void	Menu::winner_campaign() {
	if (!this->musicIsPlaying)
	{
		this->musicIsPlaying = true;
		main_event->soundrender->playMusic("victory");
	}
	// std::cout << "main_event->winner_campaign " << main_event->draw_winner_campaign << std::endl;
	print_surface(this->winner_campaign_txt, this->winner_campaign_txt, 400, 400, 0);
}

void	Menu::lose_campaign() {
	if (!this->musicIsPlaying)
	{
		this->musicIsPlaying = true;
		main_event->soundrender->stopMusic();
		main_event->soundrender->stopSounds();
		main_event->soundrender->playSound("lose");
	}
	// std::cout << "main_event->lose_campaign " << main_event->draw_lose_campaign << std::endl;
	print_surface(this->lose_campaign_txt, this->lose_campaign_txt, 400, 400, 0);
}

void	Menu::end_campaign() {
	if (!this->musicIsPlaying)
	{
		this->musicIsPlaying = true;
		main_event->soundrender->playMusic("victory_final");
	}
	// std::cout << "main_event->end_campaign " << main_event->draw_end_campaign << std::endl;
	print_surface(this->winner_game_txt, this->winner_game_txt, 400, 400, 0);
}

void	Menu::campaign() {
	print_surface(this->str_campaign_new, this->str_campaign_new_selected, 400, 400, MENU_CAMPAIGN_NEW);
	print_surface(this->str_campaign_continue, this->str_campaign_continue_selected, 400, 500, MENU_CAMPAIGN_CONTINUE);
	print_surface(this->str_campaign_coop, this->str_campaign_coop_selected, 400, 600, MENU_CAMPAIGN_COOP);
	print_surface(this->str_return, this->str_return_selected, 400, 700, MENU_CAMPAIGN_RETURN);
}

void	Menu::arena() {
	print_surface(this->str_2players, this->str_2players_selected, 400, 400, MENU_ARENA_2P);
	print_surface(this->str_3players, this->str_3players_selected, 400, 500, MENU_ARENA_3P);
  print_surface(this->str_4players, this->str_4players_selected, 400, 600, MENU_ARENA_4P);
	print_surface(this->str_5players, this->str_5players_selected, 400, 700, MENU_ARENA_5P);
	print_surface(this->str_return, this->str_return_selected, 400, 800, MENU_ARENA_RETURN);
}

void	Menu::multiplayer() {
	print_surface(this->str_2players, this->str_2players_selected, 400, 400, MENU_MULTI_2P);
	print_surface(this->str_3players, this->str_3players_selected, 400, 500, MENU_MULTI_3P);
  print_surface(this->str_4players, this->str_4players_selected, 400, 600, MENU_MULTI_4P);
	print_surface(this->str_5players, this->str_5players_selected, 400, 700, MENU_MULTI_5P);
	print_surface(this->str_return, this->str_return_selected, 400, 800, MENU_MULTI_RETURN);
}

void	Menu::config() {
	print_surface(this->str_config_1, this->str_config_1_selected, 200, 400, MENU_CONFIG_PLAYER1);
	if (main_event->joystick->config[0] == 0)
		print_surface(this->str_player_controller_selected, this->str_player_controller_selected, 600, 400, MENU_CONFIG_PLAYER1);
	else
		print_surface(this->str_player_keyboard_selected, this->str_player_keyboard_selected, 600, 400, MENU_CONFIG_PLAYER1);

	print_surface(this->str_config_2, this->str_config_2_selected, 200, 500, MENU_CONFIG_PLAYER2);
	if (main_event->joystick->config[1] == 0)
		print_surface(this->str_player_controller_selected, this->str_player_controller_selected, 600, 500, MENU_CONFIG_PLAYER2);
	else
		print_surface(this->str_player_keyboard_selected, this->str_player_keyboard_selected, 600, 500, MENU_CONFIG_PLAYER2);

	print_surface(this->str_config_3, this->str_config_3_selected, 200, 600, MENU_CONFIG_PLAYER3);
	if (main_event->joystick->config[2] == 0)
		print_surface(this->str_player_controller_selected, this->str_player_controller_selected, 600, 600, MENU_CONFIG_PLAYER3);
	else
		print_surface(this->str_player_keyboard_selected, this->str_player_keyboard_selected, 600, 600, MENU_CONFIG_PLAYER3);

	print_surface(this->str_config_4, this->str_config_4_selected, 200, 700, MENU_CONFIG_PLAYER4);
	if (main_event->joystick->config[3] == 0)
		print_surface(this->str_player_controller_selected, this->str_player_controller_selected, 600, 700, MENU_CONFIG_PLAYER4);
	else
		print_surface(this->str_player_keyboard_selected, this->str_player_keyboard_selected, 600, 700, MENU_CONFIG_PLAYER4);

	print_surface(this->str_config_5, this->str_config_5_selected, 200, 800, MENU_CONFIG_PLAYER5);
	if (main_event->joystick->config[4] == 0)
		print_surface(this->str_player_controller_selected, this->str_player_controller_selected, 600, 800, MENU_CONFIG_PLAYER5);
	else
		print_surface(this->str_player_keyboard_selected, this->str_player_keyboard_selected, 600, 800, MENU_CONFIG_PLAYER5);

	print_surface(this->str_return, this->str_return_selected, 400, 900, MENU_CONFIG_RETURN);
}

void	Menu::exit_game() {
	print_surface(this->str_exit_confirm, this->str_exit_confirm_selected, 400, 400, MENU_EXIT_CONFIRM);
	print_surface(this->str_return, this->str_return_selected, 400, 500, MENU_EXIT_RETURN);
}

void	Menu::print_surface(SDL_Surface * str, SDL_Surface * str_select, int x, int y, int type) {
	this->position.x = x;
	this->position.y = y;
	if (type == this->detail_menu_selected)
		SDL_BlitSurface(str_select, NULL, this->ecran_menu, &this->position);
	else
		SDL_BlitSurface(str, NULL, this->ecran_menu, &this->position);
}

void  Menu::big_menu() {
	static int musicPlaying = false;

	if (!musicPlaying) {
		musicPlaying = true;
		main_event->soundrender->playMusic("music");
	}

	if (true == main_event->game_playing) // Si partie en cours
		print_surface(this->str_resume_game, this->str_resume_game_selected, 400, 300, RESUME_GAME);
	print_surface(this->str_campaign, this->str_campaign_selected, 400, 400, MENU_CAMPAIGN);
	print_surface(this->str_arena, this->str_arena_selected, 400, 500, MENU_ARENA);
	print_surface(this->str_multiplayer, this->str_multiplayer_selected, 400, 600, MENU_MULTIPLAYER);
	print_surface(this->str_config, str_config_selected, 400, 700, MENU_CONFIG);

	if (true == main_event->option_arcade)
		print_surface(this->str_arcade, this->str_arcade_selected, 400, 800, MENU_EXIT);
	else
		print_surface(this->str_exit, this->str_exit_selected, 400, 800, MENU_EXIT);
}

void Menu::init() {
	this->joystick_number = SDL_NumJoysticks();

	this->SansPosterBold = TTF_OpenFont("src/menu/fonts/GoldenAge.ttf", 64);
	this->white = {255, 255, 255, 1};
	this->blue = {0, 0, 255, 1};
	this->red = {255, 0, 0, 1};
	SDL_JoystickEventState(SDL_ENABLE);
	std::cout << "nombre: " << this->joystick_number << std::endl;
	main_event->joystick->init_joystick();


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
	this->str_arcade = TTF_RenderText_Blended(this->SansPosterBold, "Arcade MODE", this->white);
	this->str_arcade_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> NO EXIT <<", this->red);
	this->str_exit = TTF_RenderText_Blended(this->SansPosterBold, "Exit Game", this->white);
	this->str_exit_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Exit Game <<", this->red);
	this->str_exit_confirm = TTF_RenderText_Blended(this->SansPosterBold, "Confirm exit game", this->white);
	this->str_exit_confirm_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Confirm exit game <<", this->red);
	this->str_return = TTF_RenderText_Blended(this->SansPosterBold, "Return", this->white);
	this->str_return_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Return <<", this->red);

	this->str_config_1 = TTF_RenderText_Blended(this->SansPosterBold, "Player 1:", this->white);
	this->str_config_2 = TTF_RenderText_Blended(this->SansPosterBold, "Player 2:", this->white);
	this->str_config_3 = TTF_RenderText_Blended(this->SansPosterBold, "Player 3:", this->white);
	this->str_config_4 = TTF_RenderText_Blended(this->SansPosterBold, "Player 4:", this->white);
	this->str_config_5 = TTF_RenderText_Blended(this->SansPosterBold, "Player 5:", this->white);
	this->str_config_1_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Player 1:", this->red);
	this->str_config_2_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Player 2:", this->red);
	this->str_config_3_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Player 3:", this->red);
	this->str_config_4_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Player 4:", this->red);
	this->str_config_5_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Player 5:", this->red);

	this->str_player_controller_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Controller <<", this->red);
	this->str_player_keyboard_selected = TTF_RenderText_Blended(this->SansPosterBold, ">> Keyboard <<", this->red);


	this->lose_campaign_txt = TTF_RenderText_Blended(this->SansPosterBold, "You Lose !", this->red);
	this->winner_campaign_txt = TTF_RenderText_Blended(this->SansPosterBold, "You win ! Next level...", this->red);
	this->winner_game_txt = TTF_RenderText_Blended(this->SansPosterBold, "You win the game !", this->red);

	this->winner = (SDL_Surface **)std::malloc(sizeof(SDL_Surface *) * 5);
	if (NULL == this->winner) {
		this->w_error("Menu::init winner allocation error");
		throw std::exception();
	}
	this->winner[0] = TTF_RenderText_Blended(this->SansPosterBold, "Player 1 Victory", this->blue);
	this->winner[1] = TTF_RenderText_Blended(this->SansPosterBold, "Player 2 Victory", this->blue);
	this->winner[2] = TTF_RenderText_Blended(this->SansPosterBold, "Player 3 Victory", this->blue);
	this->winner[3] = TTF_RenderText_Blended(this->SansPosterBold, "Player 4 Victory", this->blue);
	this->winner[4] = TTF_RenderText_Blended(this->SansPosterBold, "Player 5 Victory", this->blue);
}

void Menu::intro_start() {
  if (false == this->introstart) {
    glClear((GL_COLOR_BUFFER_BIT)| GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);
    if (NULL == this->ecran_menu)
      SDL_FreeSurface(this->current);
    this->current = NULL;
	this->current = IMG_Load("src/menu/assets/intro_start-2.bmp");
    // this->current = IMG_Load("src/menu/assets/bomberman-intro-3.bmp");
    if (NULL == this->current) {
      std::cerr << "Menu::intro_start load image error " << SDL_GetError() << std::endl;
      throw std::exception();
    }
    globject::display_menu(this->current);
    SDL_GL_SwapWindow(globject::_displayWindow);
  }
}

void  Menu::menu_selection() {
 if (NULL != this->ecran_menu) {
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

	// std::cout << "winer multi is " << main_event->draw_winner_multi << std::endl;
  if (main_event->draw_winner_multi >= 0) { // Affichage du victorieu
    this->winner_multi();
  }
  else if (main_event->draw_winner_campaign >= 0) { // Affichage du victorieu
    this->winner_campaign();

    if (main_event->draw_winner_campaign == 1) {
      main_event->make_new_game(1);
      main_event->draw_winner_campaign = 2;
    }

    // main_event->game_playing = false; // IL faut FREE l'ancienne map et relancer une game au besoin
  }
  else if (main_event->draw_lose_campaign >= 0) { // Affichage du victorieu
    this->lose_campaign();
    // main_event->game_playing = false; // IL faut FREE l'ancienne map et relancer une game au besoin
  }
  else if (main_event->draw_end_campaign >= 0) { // Affichage du victorieu
    this->end_campaign();
    // main_event->game_playing = false; // IL faut FREE l'ancienne map et relancer une game au besoin
  }
  else {
    switch(this->menu_selected) {
      case BIG_MENU:	this->big_menu(); break;
      case CAMPAIGN:	this->campaign(); break;
      case ARENA:		this->arena(); break;
      case MULTIPLAYER:	this->multiplayer(); break;
      case CONFIG:		this->config(); break;
      case EXIT:		this->exit_game();
    }
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
    main_event->joystick->read_key(0);
    usleep(50000);
  }
}

void Menu::move_menu_hor() {
	main_event->soundrender->playSound("switchselect");
	if (this->menu_selected != CONFIG)
		return ;

	int i = 0, tmp = 0;

	while (i < 5) {
		if (main_event->joystick->config[i] == 1)
			tmp++;
		i++;
	}
	if (tmp >= 2 && main_event->joystick->config[this->detail_menu_selected - MENU_CONFIG_PLAYER1] == 0)
		return ;

	if (this->detail_menu_selected == MENU_CONFIG_PLAYER1)
		main_event->joystick->config[0] = (main_event->joystick->config[0] == 0) ? 1 : 0;
	else if (this->detail_menu_selected == MENU_CONFIG_PLAYER2)
		main_event->joystick->config[1] = (main_event->joystick->config[1] == 0) ? 1 : 0;
	else if (this->detail_menu_selected == MENU_CONFIG_PLAYER3)
		main_event->joystick->config[2] = (main_event->joystick->config[2] == 0) ? 1 : 0;
	else if (this->detail_menu_selected == MENU_CONFIG_PLAYER4)
		main_event->joystick->config[3] = (main_event->joystick->config[3] == 0) ? 1 : 0;
	else if (this->detail_menu_selected == MENU_CONFIG_PLAYER5)
		main_event->joystick->config[4] = (main_event->joystick->config[4] == 0) ? 1 : 0;
	main_event->joystick->save_config();
}

void  Menu::move_menu_ver(int dir) {
	main_event->soundrender->playSound("menu1");
	if (this->menu_selected == BIG_MENU) {
		if (dir == -1 && main_event->game_playing == true && this->detail_menu_selected == MENU_CAMPAIGN)
			this->detail_menu_selected = RESUME_GAME;
		else if (dir == -1 && main_event->game_playing == false && this->detail_menu_selected == MENU_CAMPAIGN)
			this->detail_menu_selected = MENU_EXIT;
		else if (dir == -1 && this->detail_menu_selected == RESUME_GAME)
			this->detail_menu_selected = MENU_EXIT;
		else if (dir == 1 && main_event->game_playing == true && this->detail_menu_selected == MENU_EXIT)
			this->detail_menu_selected = RESUME_GAME;
		else if (dir == 1 && main_event->game_playing == false && this->detail_menu_selected == MENU_EXIT)
			this->detail_menu_selected = MENU_CAMPAIGN;
		else
		this->detail_menu_selected += dir;
	}

  else if (this->menu_selected == CAMPAIGN) {
    if (dir == -1 && this->detail_menu_selected == MENU_CAMPAIGN_NEW)
      this->detail_menu_selected = MENU_CAMPAIGN_RETURN;
    else if (dir == 1 && this->detail_menu_selected == MENU_CAMPAIGN_RETURN)
      this->detail_menu_selected = MENU_CAMPAIGN_NEW;
    else
     this->detail_menu_selected += dir;
  }

  else if (this->menu_selected == ARENA) {
    if (dir == -1 && this->detail_menu_selected == MENU_ARENA_2P)
      this->detail_menu_selected = MENU_ARENA_RETURN;
    else if (dir == 1 && this->detail_menu_selected == MENU_ARENA_RETURN)
      this->detail_menu_selected = MENU_ARENA_2P;
    else
     this->detail_menu_selected += dir;
  }

  else if (this->menu_selected == MULTIPLAYER) {
    if (dir == -1 && this->detail_menu_selected == MENU_MULTI_2P)
      this->detail_menu_selected = MENU_MULTI_RETURN;
    else if (dir == 1 && this->detail_menu_selected == MENU_MULTI_RETURN)
      this->detail_menu_selected = MENU_MULTI_2P;
    else
       this->detail_menu_selected += dir;
  }

  else if (this->menu_selected == CONFIG) {
    if (dir == -1 && this->detail_menu_selected == MENU_CONFIG_PLAYER1)
      this->detail_menu_selected = MENU_CONFIG_RETURN;
    else if (dir == 1 && this->detail_menu_selected == MENU_CONFIG_RETURN)
      this->detail_menu_selected = MENU_CONFIG_PLAYER1;
    else
     this->detail_menu_selected += dir;
  }

  else if (this->menu_selected == EXIT) {
    if (this->detail_menu_selected == MENU_EXIT_CONFIRM)
      this->detail_menu_selected = MENU_EXIT_RETURN;
    else if (this->detail_menu_selected == MENU_EXIT_RETURN)
      this->detail_menu_selected = MENU_EXIT_CONFIRM;
  }
}

void  Menu::change_menu_back() {
	if (this->menu_selected == CAMPAIGN || this->menu_selected == ARENA
		|| this->menu_selected == MULTIPLAYER || this->menu_selected == CONFIG){
			this->menu_selected = BIG_MENU;
			if (main_event->game_playing == true)
				this->detail_menu_selected = RESUME_GAME;
			else
				this->detail_menu_selected = MENU_CAMPAIGN;
		}
}

void  Menu::change_menu() {
  std::cout << this->menu_selected << " vs " << RESUME_GAME << std::endl;
  if (!(this->detail_menu_selected == MENU_CAMPAIGN_RETURN
	|| this->detail_menu_selected == MENU_CONFIG_RETURN
	|| this->detail_menu_selected == MENU_EXIT_RETURN
	|| this->detail_menu_selected == MENU_ARENA_RETURN
	|| this->detail_menu_selected == MENU_MULTI_RETURN))
  {
	    main_event->soundrender->playSound("menu2");
  }
  if ( CAMPAIGN == this->menu_selected && MENU_CAMPAIGN_NEW == this->detail_menu_selected )
    Gamelauncher::campaign_new();
  else if ( CAMPAIGN == this->menu_selected && MENU_CAMPAIGN_COOP == this->detail_menu_selected )
      Gamelauncher::campaign_new_coop();
  else if (this->detail_menu_selected == MENU_CAMPAIGN) {
    this->detail_menu_selected = MENU_CAMPAIGN_NEW;
    this->menu_selected = CAMPAIGN;
  }
  else if (main_event->game_playing == true && this->detail_menu_selected == RESUME_GAME) {
    // main_event->game_playing = false;
    main_event->mode_menu = false;
  }
  else if (this->detail_menu_selected == MENU_CONFIG) {
    this->detail_menu_selected = MENU_CONFIG_PLAYER1;
    this->menu_selected = CONFIG;
  }
  else if ( this->menu_selected == MULTIPLAYER && this->detail_menu_selected == MENU_MULTI_5P )
    Gamelauncher::run_multi_5(); // Multiplayer 4 Players Launcher game
  else if ( this->menu_selected == MULTIPLAYER && this->detail_menu_selected == MENU_MULTI_4P )
    Gamelauncher::run_multi_4(); // Multiplayer 4 Players Launcher game
  else if ( this->menu_selected == MULTIPLAYER && this->detail_menu_selected == MENU_MULTI_3P )
    Gamelauncher::run_multi_3(); // Multiplayer 3 Players Launcher game
  else if ( this->menu_selected == MULTIPLAYER && this->detail_menu_selected == MENU_MULTI_2P )
    Gamelauncher::run_multi_2(); // Multiplayer 2 Players Launcher game
  else if (this->detail_menu_selected == MENU_MULTIPLAYER) {
    this->detail_menu_selected = MENU_MULTI_2P;
    this->menu_selected = MULTIPLAYER;
  }
  else if ( this->menu_selected == ARENA && this->detail_menu_selected == MENU_ARENA_5P )
    Gamelauncher::run_arena_5();
  else if ( this->menu_selected == ARENA && this->detail_menu_selected == MENU_ARENA_4P )
    Gamelauncher::run_arena_4();
  else if ( this->menu_selected == ARENA && this->detail_menu_selected == MENU_ARENA_3P )
    Gamelauncher::run_arena_3();
  else if ( this->menu_selected == ARENA && this->detail_menu_selected == MENU_ARENA_2P )
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
		main_event->soundrender->playSound("return");
    this->detail_menu_selected = MENU_CAMPAIGN;
    this->menu_selected = BIG_MENU;
  }
  else if (this->detail_menu_selected == MENU_EXIT) {
		if (false == main_event->option_arcade)
		{
			this->detail_menu_selected = MENU_EXIT_CONFIRM;
	    this->menu_selected = EXIT;
		}
  }
  else if (this->detail_menu_selected == MENU_EXIT_CONFIRM)
    main_event->exit_free();
}

Menu::Menu(Event * event) : event(event), current(NULL) {}

Menu::~Menu() {
	SDL_FreeSurface(this->str_resume_game);
	SDL_FreeSurface(this->str_resume_game_selected);
	SDL_FreeSurface(this->str_campaign);
	SDL_FreeSurface(this->str_campaign_selected);
	SDL_FreeSurface(this->str_campaign_new);
	SDL_FreeSurface(this->str_campaign_new_selected);
	SDL_FreeSurface(this->str_campaign_coop);
	SDL_FreeSurface(this->str_campaign_coop_selected);
	SDL_FreeSurface(this->str_campaign_continue);
	SDL_FreeSurface(this->str_campaign_continue_selected);
	SDL_FreeSurface(this->str_arena);
	SDL_FreeSurface(this->str_arena_selected);
	SDL_FreeSurface(this->str_2players);
	SDL_FreeSurface(this->str_2players_selected);
	SDL_FreeSurface(this->str_3players);
	SDL_FreeSurface(this->str_3players_selected);
	SDL_FreeSurface(this->str_4players);
	SDL_FreeSurface(this->str_4players_selected);
	SDL_FreeSurface(this->str_5players);
	SDL_FreeSurface(this->str_5players_selected);
	SDL_FreeSurface(this->str_multiplayer);
	SDL_FreeSurface(this->str_multiplayer_selected);
	SDL_FreeSurface(this->str_config);
	SDL_FreeSurface(this->str_config_selected);
	SDL_FreeSurface(this->str_arcade);
	SDL_FreeSurface(this->str_arcade_selected);
	SDL_FreeSurface(this->str_exit);
	SDL_FreeSurface(this->str_exit_selected);
	SDL_FreeSurface(this->str_exit_confirm);
	SDL_FreeSurface(this->str_exit_confirm_selected);
	SDL_FreeSurface(this->str_return);
	SDL_FreeSurface(this->str_return_selected);

	SDL_FreeSurface(this->winner[0]);
	SDL_FreeSurface(this->winner[1]);
	SDL_FreeSurface(this->winner[2]);
	SDL_FreeSurface(this->winner[3]);
	SDL_FreeSurface(this->winner[4]);

	std::free(this->winner);
}
