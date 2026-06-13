#ifndef H_BATTLE
#define H_BATTLE

#include <vector>
#include <iostream>

#include "entities.h"
#include "player.h"
#include "utility.h"

class Battle {

private:
  std::vector<Entities> enemy_;

public:
  Battle(std::vector<Entities> enemies);
  bool StartBattle();
};

#endif