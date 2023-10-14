#include "Potion.h"

Potion::Potion() {}

Potion::Potion(Vector position, Vector dimensions, std::string type,
               std::string description, int health_regen)
    : Item(position, dimensions, type, description), health_regen(health_regen) {
}

void Potion::use(Player* player) {
  player->health += this->health_regen;
  if (player->health > player->max_health) {
    player->health = player->max_health;
  }
}

void Potion::render(sf::RenderWindow &window) {
  window.draw(this->rectangle);
}

void Potion::update() {}