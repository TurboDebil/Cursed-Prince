#ifndef H_ENCOUNTERS
#define H_ENCOUNTERS

#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "battle.h"
#include "entities.h"
#include "player.h"

class Encounters {
  private:
    int id_;
    std::vector<std::string> content_;
  
  public:
    Encounters(int id, std::vector<std::string> content);

    void PlayEncounter(std::vector<Encounters> narrative);
    void Lose();
};

#endif