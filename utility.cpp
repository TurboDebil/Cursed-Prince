#include <random>
#include <iostream>

#include "utility.h"

int Utility::RandomGenerator(int min_value, int max_value) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(min_value, max_value);
  return dist(gen);
}

int Utility::ProtectionFromDebil(int max_value) {
  int players_choice;
  bool is_choice_valid = false;
  while (!is_choice_valid) {
	std::cin >> players_choice;
	if ((players_choice > 0) and (players_choice <= max_value)) {
	  is_choice_valid = false;
	  return players_choice;
	}
	else std::cout << "invalid choice" << std::endl;
}
}