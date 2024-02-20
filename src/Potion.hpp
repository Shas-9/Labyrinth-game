#ifndef POTION_H
#define POTION_H

#include "Item.hpp"

class Potion : public Item {
protected:
  int health_regen;

public:
  Potion();
  Potion(Vector position);
};

#endif