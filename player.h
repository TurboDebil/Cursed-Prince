#ifndef H_PLAYER
#define H_PLAYER

#include <vector>
#include <string>

#include "entities.h"

class Player {
private:
	static Player* player_instance_;
	Player() {}

public:
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	Player(Player&&) = delete;
	Player& operator=(Player&&) = delete;

	static Player* GetInstance() {
		if (player_instance_ == nullptr) {
			player_instance_ = new Player();
		}
		return player_instance_;
	}

	std::vector<Entities> temp_;
	std::vector<Entities> squad_;
	std::vector<int> merge_table_;
	int pragmatism_ = 0;
	int humanity_ = 0;
	int level_ = 2;

	void Recrut(Entities new_corpse);

	static void Destroy() {
		delete player_instance_;
		player_instance_ = nullptr;
	}

};

#endif