#include "entities.h"


int entity_id_;
std::string entity_name_;
int entity_max_hp_;
int entity_current_hp_;
int entity_armor_;
int entity_damage_[2];
int entity_armor_piercing_;
int poisoned_;
int bleeding_;
bool poisonous_;
bool bloodletting_;
bool is_alive_;


Entities::Entities(std::string name, int ints[6], bool bools[2]) {
  entity_name_ = name;
  entity_id_ = ints[0];
  entity_max_hp_ = ints[1];
  entity_current_hp_ = entity_max_hp_;
  entity_armor_ = ints[2];
  entity_damage_[0] = ints[3];
  entity_damage_[1] = ints[4];
  entity_armor_piercing_ = ints[5];
  poisoned_ = 0;
  bleeding_ = 0;
  poisonous_ = bools[0];
  bloodletting_ = bools[1];
  is_alive_ = true;
}

void Entities::TakeAttack(int damage, int armor_piercing, bool poisonous, bool bloodletting){
  int left_armor = entity_armor_ - armor_piercing;
  if (left_armor < 0) left_armor = 0;
  entity_current_hp_ = entity_current_hp_ - (damage - left_armor);
  if (entity_current_hp_ > entity_max_hp_) entity_current_hp_ = entity_max_hp_;
  if (poisonous) poisoned_ += 3;
  if (bloodletting) bleeding_ += 3;
  if (entity_current_hp_ < 1) is_alive_ = false;
}

void Entities::Attack(Entities& target) {
  int damage = Utility::RandomGenerator(entity_damage_[0], entity_damage_[1]);
  target.TakeAttack(damage, entity_armor_piercing_, poisonous_, bloodletting_);
}

void Entities::Print() {
  if (is_alive_) {
    std::cout << entity_name_ << " HP: " << entity_current_hp_ << "/" << entity_max_hp_;
    if (poisoned_ > 0) std::cout << " Poisoned for " << poisoned_ << "turns";
    if (bleeding_ > 0) std::cout << " Bleeding for " << bleeding_ << "turns";
    std::cout << std::endl;
  }
  else {
    std::cout << "Corpse of " << entity_name_ << std::endl;
  }
}

void Entities::FullPrint() {
  Print();
  std::cout << "Armor: " << entity_armor_ << ". Armor piercing: " << entity_armor_piercing_ << std::endl;
  std::cout << "Damage: " << entity_damage_[0] << "-" << entity_damage_[1] << std::endl;
  if (poisonous_) std::cout << "Can cause poisoning."<< std::endl;
  if (bloodletting_) std::cout << "Can cause bleeding" << std::endl;
  std::cout << std::endl;
}

void Entities::Heal(int amount) {
  entity_current_hp_ = entity_current_hp_ + amount;
  std::cout << entity_name_ << "healed for " << amount << "HP. " << std::endl;
  if (entity_current_hp_ > entity_max_hp_) entity_current_hp_ = entity_max_hp_;
}

void Entities::GetStatusDamage() {
  if (poisoned_ > 0) {
    entity_current_hp_ = entity_current_hp_ - poisoned_;
    std::cout << entity_name_ << "got " << poisoned_ << " damage from poison." << std::endl;
  }
  if (bleeding_ > 0) {
    entity_current_hp_ = entity_current_hp_ - bleeding_;
    std::cout << entity_name_ << "got " << bleeding_ << " damage from bleeding." << std::endl;
  }
  if (entity_current_hp_ < 1) is_alive_ = false;
}

void Entities::ApplyPoison(int amount) {
  poisoned_ = poisoned_ + amount;
}

std::string Entities::GetName() {
  return entity_name_;
}

bool Entities::IsAlive() {
  return is_alive_;
}

int Entities::GetID() {
  return entity_id_;
}