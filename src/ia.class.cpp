#include <ia.class.hpp>

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

bool Ia::get_paths(Entity *it, int dir, int or_dir) {
  if ((*it).dir == dir) {
    int direction = (*it).pretest_move((*it).dir);
    if (direction == EMPTY) {
      (*it).move(dir);
    }
    else {
      if (direction == WALL) {
          (*it).put_bomb (
            BOMB_SEC_3, (*it).pos_x, (*it).pos_y,
            BOMB, (*it).blast_radius
          );
      }
      (*it).dir = or_dir;
      return true;
    }
  }
  return false;
}

void     Ia::start( int time ) {
  std::list<Entity *>::iterator it = main_event->char_list.begin();
  std::list<Entity *>::iterator end = main_event->char_list.end();
  (void)time;
  while (it != end) {
    if ((*it)->type == ENEMY
    && !Ia::get_paths(*it, DIR_UP, DIR_RIGHT)
    && !Ia::get_paths(*it, DIR_RIGHT, DIR_BOTTOM)
    && !Ia::get_paths(*it, DIR_BOTTOM, DIR_LEFT)
    && !Ia::get_paths(*it, DIR_LEFT, DIR_UP)) {
    }
    it++;
  }
}

//printf("%f-%f\n", (*it)->pos_x, (*it)->pos_y);
