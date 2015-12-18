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
      if (*it == PLAYER) {
          return (score - 50);
      }
      else {
        return (score - 60);
      }
    }
    score += 1;
  }

  std::cout << score << '\n';
  for (std::vector<int>::iterator i = line.begin(); i != line.end(); ++i)
    std::cout << *i << ',';
  std::cout << '\n';
  return (score);
}

int    Ia::must_move_to( Entity *it ) {
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
  for ( int n=0 ; n<4 ; ++n ) {
    if (max[0] < paths[n][0]) {
      max[0] = paths[n][0];
      max[1] = n;
    }
  }
  std::cout << '='
            << DIR_UP + max[1]
            << '\n';
  return (DIR_UP + max[1]);
}

bool    Ia::play_enemy(Entity *it) {
  if ((*it).dir == ((*it).dir = Ia::must_move_to(it))) {
    /*(*it).put_bomb (
      BOMB_SEC_3, (*it).pos_x, (*it).pos_y,
      BOMB, (*it).blast_radius
    );*/
  }
  (*it).move((*it).dir);
  return (true);
}

void     Ia::start( int time ) {
  std::list<Entity *>::iterator it = main_event->char_list.begin();
  std::list<Entity *>::iterator cit = main_event->char_list.begin();
  std::list<Entity *>::iterator end = main_event->char_list.end();
  (void)time;
  while (it != end) {
    if ((*it)->type == ENEMY
    &&  Ia::play_enemy(*it) ) {

    }
    it++;
  }
  while (cit != end) {
    if ((*cit)->type == PLAYER) {
      /*std::cout << '\t'
                << (int)((*cit)->pos_x)
                << ';'
                << (int)((*cit)->pos_y)
                << ' ';*/
      break ;
    }
    cit++;
  }
}

//printf("%f-%f\n", (*it)->pos_x, (*it)->pos_y);
