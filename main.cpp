#include <vector>
#include <iostream>

#include "assets.h"
#include "player.h"
#include "battle.h"
#include "utility.h"
#include "entities.h"

int main() {
  Assets* assets_instance = Assets::GetInstance();
  assets_instance->ReadEntities();
  assets_instance->ReadEncounters();
  assets_instance->ReadExtras();
  assets_instance->ReadMerges();

  Player* player_instance = Player::GetInstance();
  
  player_instance->temp_ = assets_instance->assets_entities_;
  player_instance->merge_table_ = assets_instance->merges_;

  std::vector<Encounters> extras;

  extras = assets_instance->assets_extras_;

  int story_stage = 0;
  assets_instance->assets_encounters_.at(story_stage).PlayEncounter(extras);
  story_stage = story_stage + 1;

  while (story_stage < 4) {
	std::cout << "You are in a save and quiet space. Nice time to take care of other activities. What would you do next?" << std::endl;
	std::cout << "1. Continue the story." << std::endl;
	std::cout << "2. Find random fight in forest." << std::endl;
	std::cout << "3. Find random fight near Lowland." << std::endl;
	int choice = Utility::ProtectionFromDebil(3);
	if (choice == 1) {
	  assets_instance->assets_encounters_.at(story_stage).PlayEncounter(extras);
	  story_stage = story_stage + 1;
	}
	else if(choice == 2){
	  int number = Utility::RandomGenerator(1, player_instance->squad_.size());
	  std::vector<Entities> enemies;
	  for (int i = 0; i < number; i++) {
		enemies.push_back(assets_instance->assets_entities_.at(Utility::RandomGenerator(8, 11)));
	  }
	  Battle new_battle(enemies);
	  new_battle.StartBattle();
	}
	else {
	  int number = Utility::RandomGenerator(1, player_instance->squad_.size());
	  std::vector<Entities> enemies;
	  for (int i = 0; i < number; i++) {
		enemies.push_back(assets_instance->assets_entities_.at(Utility::RandomGenerator(12, 14)));
	  }
	  Battle new_battle(enemies);
	  new_battle.StartBattle();
	}
  }
  if (player_instance->pragmatism_ > player_instance->humanity_) {
	story_stage = story_stage + 1;
  }
  assets_instance->assets_encounters_.at(story_stage).PlayEncounter(extras);
}