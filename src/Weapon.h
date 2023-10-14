#ifndef WEAPON_INCLUDE
#define WEAPON_INCLUDE

#include "Item.h"

class Weapon : public Item {
 protected:
  bool isWithPlayer;
  int damage;

 public:
  Weapon();
  Weapon(Vector position, Vector dimensions, std::string type,
         std::string description, int damage);
  void pickUp();
  void drop();
  int use(Player* player);
};

#endif