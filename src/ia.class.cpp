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
	(void)time;

  std::list<Entity *>::iterator it = main_event->char_list.begin();
  std::list<Entity *>::iterator end = main_event->char_list.end();

  while (it != end) {
    if ((*it)->type == ENEMY) {
      if (time % 2 == 1) {
        (*it)->move(DIR_BOTTOM);
      }
      else {
        (*it)->move(DIR_UP);
      }
      break ;
    }
    it++;
  }
}
