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

/*bool Ia::play_enemy(Entity *it, int dir, int or_dir) {
  if ((*it).dir == dir) {
    int direction = (*it).pretest_move((*it).dir);
    if (direction == EMPTY) {
      (*it).move(dir);
    }
    else {
      if (direction != ENEMY) {
          (*it).put_bomb (
            BOMB_SEC_3, (*it).pos_x, (*it).pos_y,
            BOMB, (*it).blast_radius
          );
      }
      (*it).dir = or_dir;
      return (true);
    }
  }
  return (false);
}*/


int heuristic(std::vector<int> line) {
  int score = 0;

  for (
    std::vector<int>::iterator it = line.begin();
    it != line.end();
    ++it
  ) {
    if (*it == PLAYER1) {
      return (score - 5);
    }
    score += 1;
  }

  /*std::cout << ':' << score << '\t';
  for (std::vector<int>::iterator i = line.begin(); i != line.end(); ++i)
      std::cout << *i << ',';
  std::cout << '\n';*/
  return (score);
}

bool      Ia::play_enemy( Entity *it ) {
  std::vector<int> lines [4] = {
    (*it).pretest_moves(DIR_UP),
    (*it).pretest_moves(DIR_RIGHT),
    (*it).pretest_moves(DIR_BOTTOM),
    (*it).pretest_moves(DIR_LEFT),
  };
  int  paths [4][2] = {
    {heuristic(lines[0]), DIR_UP},
    {heuristic(lines[1]), DIR_RIGHT},
    {heuristic(lines[2]), DIR_BOTTOM},
    {heuristic(lines[3]), DIR_LEFT},
  };
  int  max [2] = {paths[0][0], 0};
  for ( int n=1 ; n<4 ; ++n ) {
    if (max[0] < paths[n][0]) {
      max[0] = paths[n][1];
      max[1] = n;
    }
  }
  /*std::cout << max[0]
            << ';'
            << DIR_UP + max[1]
            << '\n';*/
  (*it).move(DIR_UP + max[1]);
  return (true);
}

void     Ia::start( int time ) {
  std::list<Entity *>::iterator it = main_event->char_list.begin();
  std::list<Entity *>::iterator end = main_event->char_list.end();
  (void)time;
  while (it != end) {
    if ((*it)->type == ENEMY
    &&  Ia::play_enemy(*it) ) {
      break ;
    }
    it++;
  }
}

//printf("%f-%f\n", (*it)->pos_x, (*it)->pos_y);
