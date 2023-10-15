#ifndef POTION_H
#define POTION_H

#include "Item.h"

class Potion : public Item {
 protected:
  int health_regen;

 public:
  Potion();
  Potion(Vector position, Vector dimensions, std::string type,
         std::string description, int health_regen);
  void use(Player* player);
  void render(sf::RenderWindow &window);

  virtual void update();
};

#endif