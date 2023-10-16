#include "Item.h"

Item::Item() {}

Item::Item(Vector position, Vector dimensions, std::string type, std::string description)
  : RenderedObject(position, dimensions, type), description(description) {

}

std::string Item::getType() {
  return this->type;
}

void Item::use(Player* player) {}

void Item::update() {}