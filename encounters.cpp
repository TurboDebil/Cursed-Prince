#include "encounters.h"

Encounters::Encounters(int id, std::vector<std::string> content) {
  id_ = id;
  content_ = content;
}

void Encounters::PlayEncounter(std::vector<Encounters> narrative) {
  Player* player_instance = Player::GetInstance();
  std::vector<Encounters> empty;
  for (int i = 0; i < content_.size(); i++) {
    if (content_.at(i) == "!") {
      
      //std::cout << "Press Enter to start battle" << std::endl;
      //std::string o;
      //std::cin >> o;
      i = i + 1;
      std::vector<Entities> enemies;
      std::stringstream ss(content_.at(i));
      int temp;
      while (ss >> temp) enemies.push_back(player_instance->temp_.at(temp));
      Battle new_battle(enemies);
      bool try_it = new_battle.StartBattle();
      if (!try_it) Lose();
    }
    else if (content_.at(i) == "?") {
      int choice = Utility::ProtectionFromDebil(2);
      i = i + 1;
      if (choice == 1) {
        player_instance->humanity_ = player_instance->humanity_ + 1;
        if (content_.at(i) == "get_unit") {
          std::vector<Entities> new_units;
          i = i + 1;
          std::stringstream ss(content_.at(i));
          int temp;
          while (ss >> temp) player_instance->squad_.push_back(player_instance->temp_.at(temp));
        }
        else if (content_.at(i) == "narrative_vomiting") {
          i = i + 1;
          int vomiting = std::stoi(content_.at(i));
          narrative.at(vomiting).PlayEncounter(empty);
          i = i + 1;
        }
      }
      else {
        player_instance->pragmatism_ = player_instance->pragmatism_ + 1;
        if (content_.at(i) == "get_unit") {
          std::vector<Entities> new_units;
          i = i + 2;
          std::stringstream ss(content_.at(i));
          int temp;
          while (ss >> temp) player_instance->squad_.push_back(player_instance->temp_.at(temp));
        }
        else if (content_.at(i) == "narrative_vomiting") {
          i = i + 2;
          int vomiting = std::stoi(content_.at(i));
          narrative.at(vomiting).PlayEncounter(empty);
        }
      }
    }
    else if (content_.at(i) == "??") {
      int choice = Utility::ProtectionFromDebil(3);
      i = i + 1;
      if (choice == 1) {
        player_instance->humanity_ = player_instance->humanity_ + 1;
        if (content_.at(i) == "get_unit") {
          std::vector<Entities> new_units;
          i = i + 1;
          std::stringstream ss(content_.at(i));
          int temp;
          while (ss >> temp) player_instance->squad_.push_back(player_instance->temp_.at(temp));
        }
      }
      else if(choice == 2) {
        player_instance->pragmatism_ = player_instance->pragmatism_ + 1;
        if (content_.at(i) == "get_unit") {
          std::vector<Entities> new_units;
          i = i + 2;
          std::stringstream ss(content_.at(i));
          int temp;
          while (ss >> temp) player_instance->squad_.push_back(player_instance->temp_.at(temp));
        }
      }
      else {
        player_instance->pragmatism_ = player_instance->pragmatism_ + 2;
        if (content_.at(i) == "get_unit") {
          std::vector<Entities> new_units;
          i = i + 3;
          std::stringstream ss(content_.at(i));
          int temp;
          while (ss >> temp) player_instance->squad_.push_back(player_instance->temp_.at(temp));
        }
      }

    }
    else std::cout << content_[i] << std::endl;

  }
}

void Encounters::Lose() {
  std::cout << "In the name of Light, you dead. Lost in times, forgotten for ages. There story of you and your dinasty ends...";
}
