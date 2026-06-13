#include "battle.h"

Battle::Battle(std::vector<Entities> enemies) {
	enemy_ = enemies;
}

bool Battle::StartBattle() {
  Player* player_instance = Player::GetInstance();
  
  int round = 0;
  int enemies_number = enemy_.size();
  int allies_number = player_instance->squad_.size();
  while (std::min(enemies_number, allies_number) > 0) {
	round = round + 1;
	std::cout << "Round " << round << std::endl;
	std::cout << "Your squad: " << std::endl << std::endl;
	for (int i = 0; i < allies_number; i++) player_instance->squad_.at(i).FullPrint();
	std::cout << "Enemy squad: " << std::endl;
	for (int i = 0; i < enemy_.size(); i++) enemy_.at(i).FullPrint();
	//undeads
	for (int i = 0; i < allies_number; i++) {
	  std::cout << "Turn of " << player_instance->squad_.at(i).GetName() << std::endl;
	  player_instance->squad_.at(i).GetStatusDamage();
	  if (player_instance->squad_.at(i).IsAlive()) {
		if(enemies_number > 0){
		  std::cout << "Choose target:" << std::endl;
		  for (int j = 0; j < enemy_.size(); j++) {
		    std::cout << j + 1 << " ";
		    enemy_.at(j).Print();
		  }
		  int chosen_target = Utility::ProtectionFromDebil(enemy_.size()) - 1;
		  player_instance->squad_.at(i).Attack(enemy_.at(chosen_target));
		  if (!enemy_.at(chosen_target).IsAlive()) enemies_number = enemies_number - 1;
		}
	  }
	  else {
		std::cout << player_instance->squad_.at(i).GetName() << "killed by status damage" << std::endl;
	  }
	}
	for(int i = 0; i < player_instance->squad_.size(); i++){
	  if (!player_instance->squad_.at(i).IsAlive()) {
		player_instance->squad_.erase(player_instance->squad_.begin() + i);
		i = i - 1;
		allies_number = allies_number - 1;
	  }
	}
	//enemies
	if (allies_number > 0 and enemies_number > 0) {
	  for (int i = 0; i < enemy_.size(); i++) {
		enemy_.at(i).GetStatusDamage();
		if(enemy_.at(i).IsAlive() and allies_number > 0){
		  int random_target = Utility::RandomGenerator(0, player_instance->squad_.size() - 1);
		  enemy_.at(i).Attack(player_instance->squad_.at(random_target));
		  if (!player_instance->squad_.at(random_target).IsAlive()) {
			std::cout << player_instance->squad_.at(random_target).GetName() << " is dead!" << std::endl;
			player_instance->squad_.erase(player_instance->squad_.begin() + random_target);
			allies_number = allies_number - 1;
		  }
		}
	  }
	}
	//prince
	for(int x = 0; x < player_instance->level_ / 2; x++){
	  bool turned = true;
      std::cout << "Prince turn. "; 
	  while (turned) {
	    std::cout << "Choose ability:" << std::endl;
	    std::cout << "1. Basic necromancy" << std::endl;
		std::cout << "2. Merge undeads" << std::endl;
		std::cout << "3. Skip turn" << std::endl;
	    int choice = Utility::ProtectionFromDebil(3);
	    if(choice == 1) {
	      std::cout << "Choose target:" << std::endl;
		  for (int j = 0; j < enemy_.size(); j++) {
		    std::cout << j + 1 << " ";
		    enemy_.at(j).Print();
		  }
		  std::cout << enemy_.size() + 1 << " back" << std::endl;
		  int target = Utility::ProtectionFromDebil(enemy_.size() + 1);
		  if (target < enemy_.size() + 1) {
		    if(enemy_.at(target-1).IsAlive()){
		      enemy_.at(target - 1).ApplyPoison(player_instance->level_);
		      std::cout << enemy_.at(target - 1).GetName() << "poisoned by necromany." << std::endl;
		      turned = false;
		    }
		    else {
			  int id = enemy_.at(target-1).GetID();
			  Entities rejuvinated = player_instance->temp_.at(id);
			  player_instance->Recrut(rejuvinated);
			  enemy_.erase(enemy_.begin() + target - 1);
			  allies_number = allies_number + 1;
			  turned = false;
		    }
		  }
	    }
		else if (choice == 2) {
		  std::cout << "Choose targets" << std::endl;
		  for (int y = 0; y < allies_number; y++) {
			std::cout << y + 1;
			player_instance->squad_.at(y).Print();
		  }
		  int a, b;
		  std::cin >> a >> b;
		  int aa = player_instance->squad_.at(a-1).GetID();
		  int bb = player_instance->squad_.at(b-1).GetID();
		  bool is_merged = false;
		  for (int m = 0; m < player_instance->merge_table_.size(); m++) {
		    if(std::min(aa, bb) == player_instance->merge_table_.at(m) and std::max(aa, bb) == player_instance->merge_table_.at(m+1)){
			  player_instance->squad_.erase(player_instance->squad_.begin() + std::max(a, b) - 1);
			  player_instance->squad_.erase(player_instance->squad_.begin() + std::min(a, b) - 1);
			  player_instance->squad_.push_back(player_instance->temp_.at(player_instance->merge_table_.at(m + 2)));
			  m = player_instance->merge_table_.size();
			  is_merged = true;
			  break;
			}
			m = m + 2;
		  }
		  if (!is_merged) {
			player_instance->squad_.erase(player_instance->squad_.begin() + std::max(a, b) - 1);
			player_instance->squad_.erase(player_instance->squad_.begin() + std::min(a, b) - 1);
			player_instance->squad_.push_back(player_instance->temp_.at(0));
		  }
		}
		else {
		  break;
		}
	  }
	}

  }
  if (allies_number == 0) {
    std::cout << "LOSE";
	return false;
  }
  else {
	std::cout << "WIN";
	player_instance->level_ = player_instance->level_ + 1;
	return true;
  }
}