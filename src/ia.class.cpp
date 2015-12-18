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


int heuristic(std::vector<int> line) {
  int score = 0;

  for (
    std::vector<int>::iterator it = line.begin();
    it != line.end();
    ++it
  ) {
    if (*it == PLAYER || *it == BOMB) {
      if (*it == BOMB) {
        return (score - 60);
      }
      else {
        return (score - 50);
      }
    }
    score += 1;
  }
  return (score);
}


int    Ia::must_move_to( Enemy *it ) {
  std::vector<int> lines [4] = {
    (*it).pretest_moves(DIR_UP),
    (*it).pretest_moves(DIR_BOTTOM),
    (*it).pretest_moves(DIR_LEFT),
    (*it).pretest_moves(DIR_RIGHT),
  };
  int  paths [4][2] = {
    {heuristic(lines[0]), DIR_UP},
    {heuristic(lines[1]), DIR_BOTTOM},
    {heuristic(lines[2]), DIR_LEFT},
    {heuristic(lines[3]), DIR_RIGHT},
  };
  int  max [2] = {paths[0][0], 0};
  int  min [2] = {paths[0][0], 0};
  for ( int n=0 ; n<4 ; ++n ) {
    if (max[0] < paths[n][0]) {
      max[0] = paths[n][0];
      max[1] = n;
    }
    if (min[0] > paths[n][0]) {
      min[0] = paths[n][0];
      min[1] = n;
    }
  }
  if (min[0] <= 0 || ((*it).pretest_move((*it).dir) != EMPTY)) {
    return (DIR_UP + max[1]);
  }
  else {
    return ((*it).dir);
  }
}

bool    Ia::play_enemy(Enemy *it) {
  if ((*it).dir == ((*it).dir = Ia::must_move_to(it))) {
    std::cout << (*it).memory << "\n";
    if ((*it).memory < 5) {
      (*it).put_bomb (
        BOMB_SEC_3, (*it).pos_x, (*it).pos_y,
        BOMB, (*it).blast_radius
      );
    }
    if ((*it).memory < 230) {
      (*it).memory += 1;
    }
    else {
      (*it).memory = 0;
    }
  }
  (*it).move((*it).dir);
  return (true);
}

void     Ia::start( int time ) {
  std::list<Entity *>::iterator it = main_event->char_list.begin();
  std::list<Entity *>::iterator end = main_event->char_list.end();

  (void)time;
  while (it != end) {
    if ((*it)->type == ENEMY
    &&  Ia::play_enemy(static_cast<Enemy*> (*it)) ) {
    }
    it++;
  }
}
