#include <ia.class.hpp>
#include <entity.class.hpp>

Ia::Ia( ) : layer(1) {
}

Ia::Ia( int layer ) : layer(layer) {
}

Ia::Ia( Ia const & src ) {
  (void)src;
  //(*this).layer = (*src).layer - 1;
}

Ia & Ia::operator=( Ia const & rhs ) {
	if (this != &rhs) {}
	return (*this);
}

Ia::~Ia( void ) {
	// delete this->soundrender;
}

void 	Ia::start( int time ) {
  std::list<Entity *>::iterator it = main_event->char_list.begin();
  std::list<Entity *>::iterator end = main_event->char_list.end();
  int direction;

  (void)time;
  printf("start\n");
  while (it != end) {
    printf("\tscope\n");
    if ((*it)->type == ENEMY) {
      /// Up
      if ((*it)->dir == DIR_UP) {
        direction = (*it)->check_move((*it)->pos_x, (*it)->pos_y - 0.08f);
        if (direction == EMPTY) {
          (*it)->move(DIR_UP);
        }
        else {
          if (direction == WALL) {
            (*it)->put_bomb(BOMB_SEC_3, (*it)->pos_x, (*it)->pos_y, BOMB, (*it)->blast_radius);
          }
          (*it)->dir = DIR_RIGHT;
        }
      }

      /// Right

      if ((*it)->dir == DIR_RIGHT) {
        direction = (*it)->check_move((*it)->pos_x + 0.08f*3, (*it)->pos_y);
        if (direction == EMPTY) {
          (*it)->move(DIR_RIGHT);
        }
        else {
          if (direction == WALL) {
            (*it)->put_bomb(BOMB_SEC_3, (*it)->pos_x, (*it)->pos_y, BOMB, (*it)->blast_radius);
          }
          (*it)->dir = DIR_BOTTOM;
        }
      }

      /// Bottom
      if ((*it)->dir == DIR_BOTTOM) {
        direction = (*it)->check_move((*it)->pos_x, (*it)->pos_y + 0.08f);
        if (direction == EMPTY) {
          (*it)->move(DIR_BOTTOM);
        }
        else {
          if (direction == WALL) {
            (*it)->put_bomb(BOMB_SEC_3, (*it)->pos_x, (*it)->pos_y, BOMB, (*it)->blast_radius);
          }
          (*it)->dir = DIR_LEFT;
        }
      }

      /// Left
      if ((*it)->dir == DIR_LEFT) {
        direction = (*it)->check_move((*it)->pos_x - 0.08f*3, (*it)->pos_y);

        if (direction == EMPTY) {
          (*it)->move(DIR_LEFT);
        }
        else {
          if (direction == WALL) {
            (*it)->put_bomb(BOMB_SEC_3, (*it)->pos_x, (*it)->pos_y, BOMB, (*it)->blast_radius);
          }
          (*it)->dir = DIR_UP;
        }
      }
    }
    it++;
  }
}

//printf("%f-%f\n", (*it)->pos_x, (*it)->pos_y);
