#ifndef H_ENTITIES
#define H_ENTITIES

#include <string>
#include <vector>
#include <iostream>

#include "utility.h"

class Entities {
  
  private:
    int entity_id_;
    std::string entity_name_;
    int entity_max_hp_;
    int entity_current_hp_;
    int entity_armor_;
    int entity_damage_[2];
    int entity_armor_piercing_;
    int poisoned_ = 0;
    int bleeding_ = 0;
    bool poisonous_;
    bool bloodletting_;
    bool is_alive_;

  public:
    Entities(std::string name, int ints[6], bool bools[2]);
    void TakeAttack(int damage, int armor_piercing, bool poisonous, bool bloodletting);
    void Attack(Entities& target);
    void Print();
    void FullPrint();
    void Heal(int amount);
    void GetStatusDamage();
    void ApplyPoison(int amount);
    std::string GetName();
    bool IsAlive();
    int GetID();
};

#endif