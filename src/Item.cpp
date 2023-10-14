#include "Item.h"

Item::Item() {}

Item::Item(Vector postion, Vector dimensions, std::string type,
           std::string description)
    : RenderedObject(position, type), description(description) {
      this->dimensions = dimensions;
    }

std::string Item::getType() {
  return this->type;
}