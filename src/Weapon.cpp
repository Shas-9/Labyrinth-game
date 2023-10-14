#include "Weapon.h"

Weapon::Weapon() {}

Weapon::Weapon(Vector position, Vector dimensions, std::string type,
               std::string description, int damage)
    : Item(position, dimensions, type, description), damage(damage) {}

int Weapon::use(Player* player) {
  return player->attack_damage + this->damage;
}

void Weapon::pickUp() {
  this->isWithPlayer = true;
}

void Weapon::drop() {
  this->isWithPlayer = false;
}