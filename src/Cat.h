#ifndef CAT_H
#define CAT_H

#include "Item.h"

// Cat class: The item that the player needs to pick up to end and win the game
class Cat : public Item {

public:
  Cat();
  Cat(Vector position);
  int getValue();
};

#endif