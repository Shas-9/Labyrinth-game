#include "Potion.h"

Potion::Potion() {}

Potion::Potion(Vector position, Vector dimensions, std::string type,
               std::string description, int health_regen)
    : Item(position, dimensions, type, description), health_regen(health_regen) {
}

void Potion::use(Player* player) {
  player->setHealth(player->getHealth() + this->health_regen);
  if (player->getHealth() > player->getMaxHealth()) {
    player->setHealth(player->getMaxHealth());
  }
}

void Potion::render(sf::RenderWindow &window) {
  window.draw(*this->rectangle);
}

void Potion::update() {}