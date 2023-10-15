#include "Item.h"

Item::Item() {}

Item::Item(Vector position, Vector dimensions, std::string type,
           std::string description)
    : RenderedObject(position, type), description(description) {
      this->dimensions = dimensions;
    }

std::string Item::getType() {
  return this->type;
}

void Item::use(Player* player) {}

void Item::update() {}