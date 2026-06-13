#include "player.h"

Player* Player::player_instance_;

void Player::Recrut(Entities new_corpse) {
  squad_.push_back(new_corpse);
}