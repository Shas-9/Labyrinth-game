#ifndef POTION_H
#define POTION_H

#include "Item.h"
#include "Player.h"

class Potion : public Item {
 protected:
  int health_regen;

 public:
  Potion();
  Potion(Vector position, Vector dimensions, std::string type,
         std::string description, int health_regen);

  void use(Player* player) override;

  virtual void update();
};

#endif