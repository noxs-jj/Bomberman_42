#include <joystick.hpp>
#include <event.class.hpp>
#include <Menu.class.hpp>

Joystick::Joystick() {}
Joystick::~Joystick() {}
// Joystick::Joystick( Joystick const & src ) {}
// Joystick::Joystick & operator=( Joystick const & rhs ) {}

void Joystick::read_key(int mode) {
  SDL_Event           event;
  int i = 0;

  if (mode == 0){
    while (SDL_PollEvent(&event) && main_event->event_running == true) {
      if (event.type == SDL_KEYDOWN) {
        std::cout << "(event).key.keysym.sym " << (event).key.keysym.sym << std::endl;
        switch((event).key.keysym.sym) {
          case SDLK_ESCAPE:   main_event->exit_free();
          break;

          case SDLK_SPACE:    if (false == main_event->menu->introstart) {
            main_event->menu->introstart = true;
            main_event->mode_menu = true;
          }
          break;

          case SDLK_DOWN:     main_event->menu->move_menu_ver(1); break;
          case SDLK_UP:       main_event->menu->move_menu_ver(-1); break;
          case SDLK_RIGHT:    std::cout << "hey" << std::endl; break;
          case SDLK_LEFT:     std::cout << "hey" << std::endl; break;
          case SDLK_RETURN:   if (main_event->draw_winner_multi != 0
            || main_event->draw_winner_campaign != 0
            || main_event->draw_lose_campaign != 0
            || main_event->draw_end_campaign != 0) {
              main_event->draw_winner_multi = 0;
              main_event->draw_winner_campaign = 0;
              main_event->draw_lose_campaign = 0;
              main_event->draw_end_campaign = 0;
              main_event->mode_menu = false;
            }
            else
            main_event->menu->change_menu();
            break;

            case SDLK_p:        if (true == main_event->mode_menu && main_event->game_playing == true)
            main_event->mode_menu = false;
            else if (main_event->game_playing == true)
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
        // JOYSTICK BUTTON
        else if (event.type == SDL_JOYBUTTONDOWN) {
          switch (event.cbutton.button) {
            case 0:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 1:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 2:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 3:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 4:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 5:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 6:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 7:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 8:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 9:   fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 10:  fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 11:  fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            case 12:  fprintf(stdout, "joystick[%d] button[%d] state[%d]\n", event.jbutton.which, event.jbutton.button, event.jbutton.state); break;
            default: break;
          }
        }
        // JOYSTICK CROIX DIRECTIONNEL
        else if (event.type == SDL_JOYHATMOTION) {
          if (0 == event.jhat.hat && 0 != event.jhat.value)
          {
            switch (event.jhat.value) {
              case SDL_HAT_UP:        fprintf(stdout, "joystick[%d] UP state[%d]\n", event.jbutton.which, event.jhat.hat); break;
              case SDL_HAT_LEFTUP:    fprintf(stdout, "joystick[%d] UP+LEFT state[%d]\n", event.jbutton.which, event.jhat.hat); break;
              case SDL_HAT_LEFT:      fprintf(stdout, "joystick[%d] LEFT state[%d]\n", event.jbutton.which, event.jhat.hat); break;
              case SDL_HAT_LEFTDOWN:  fprintf(stdout, "joystick[%d] DOWN+LEFT state[%d]\n", event.jbutton.which, event.jhat.hat); break;
              case SDL_HAT_DOWN:      fprintf(stdout, "joystick[%d] DOWN state[%d]\n", event.jbutton.which, event.jhat.hat); break;
              case SDL_HAT_RIGHTDOWN: fprintf(stdout, "joystick[%d] DOWN+RIGHT state[%d]\n", event.jbutton.which, event.jhat.hat); break;
              case SDL_HAT_RIGHT:     fprintf(stdout, "joystick[%d] RIGHT state[%d]\n", event.jbutton.which, event.jhat.hat); break;
              case SDL_HAT_RIGHTUP:   fprintf(stdout, "joystick[%d] UP+RIGHT state[%d]\n", event.jbutton.which, event.jhat.hat); break;
              case SDL_HAT_CENTERED:  fprintf(stdout, "joystick[%d] CENTERED state[%d]\n", event.jbutton.which, event.jhat.hat); break;
              default:                break;
            }
          }
        }
      }
    }


  }
