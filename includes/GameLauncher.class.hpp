#ifndef GAMELAUNCHER_CLASS_HPP
# define GAMELAUNCHER_CLASS_HPP

# include <ft42.class.hpp>

class Gamelauncher : ft42 {
public:
  Gamelauncher();
  virtual ~Gamelauncher();

  static void  campaign_new();
  static void  campaign_new_coop();

  static void  run_multi_2();
  static void  run_multi_3();
  static void  run_multi_4();
  static void  run_multi_5();

  static void  run_arena_2();
  static void  run_arena_3();
  static void  run_arena_4();
  static void  run_arena_5();

};

#endif
