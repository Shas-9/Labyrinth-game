#ifndef WEAPON_INCLDUE
#define WEAPON_INCLUDE

#include "Item.h"

class Weapon : public Item {
 protected:
  bool isWithPlayer;
  int damage;

 public:
  Weapon();
  void pickUp();
  void drop();
  void use();
};

#endif