#include "assets.h"

Assets* Assets::assets_instance_;

void Assets::ReadEntities() {
  std::ifstream asset_file("entities_assets.txt");
  std::string line;
  while (std::getline(asset_file, line)) {
	int ints[6];
	std::string name;
	bool bools[2];
	if (line == "Start") {
      std::getline(asset_file, line);
	  ints[0] = std::stoi(line);
	  std::getline(asset_file, line);
	  name = line;
	  for (int i = 0; i < 5; i++) {
	    std::getline(asset_file, line);
	    ints[i + 1] = std::stoi(line);
	  }
	  for (int i = 0; i < 2; i++) {
	    std::getline(asset_file, line);
	    if (line == "true") {
	      bools[i] = true;
		}
		else {
	      bools[i] = false;
		}
	  }
	  Entities new_entity(name, ints, bools);
	  assets_entities_.push_back(new_entity);
    }
  }

  asset_file.close();
}

void Assets::ReadEncounters() {
  std::ifstream asset_file("encounters_assets.txt");
  std::string line;

  while (std::getline(asset_file, line)) {
	if (line == "Start") {
	  std::getline(asset_file, line);
	  int id = std::stoi(line);
	  std::vector<std::string> strings;
	  std::getline(asset_file, line);
	  while (line != "Stop") {
		strings.push_back(line);
		std::getline(asset_file, line);
	  }
	  Encounters new_encounter(id, strings);
	  assets_encounters_.push_back(new_encounter);
	}
  }

  asset_file.close();
}

void Assets::ReadExtras() {
  std::ifstream asset_file("extras_assets.txt");
  std::string line;

  while (std::getline(asset_file, line)) {
	if (line == "Start") {
	  std::getline(asset_file, line);
	  int id = std::stoi(line);
	  std::vector<std::string> strings;
	  std::getline(asset_file, line);
	  while (line != "Stop") {
		strings.push_back(line);
		std::getline(asset_file, line);
	  }
	  Encounters new_encounter(id, strings);
	  assets_extras_.push_back(new_encounter);
	}
  }

  asset_file.close();
}

void Assets::ReadMerges(){
  std::ifstream asset_file("merges_assets.txt");
  std::string line;
  int new_number;
  while (std::getline(asset_file, line)) {
	  new_number = std::stoi(line);
	  merges_.push_back(new_number);
  }

  asset_file.close();
}