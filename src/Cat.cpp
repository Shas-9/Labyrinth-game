#include "Cat.h"

Cat::Cat() {}

Cat::Cat(Vector position, Vector dimensions, std::string type, std::string description)
    : Item(position, dimensions, type, description) {
      this->isWithPlayer = false;
}

void Cat::render(sf::RenderWindow &window) {
  window.draw(this->rectangle);
}

void Cat::use(Player* player) {
  this->isWithPlayer = true;
}

bool Cat::getIsWithPlayer() {
  return this->isWithPlayer;
}

void Cat::update() {}