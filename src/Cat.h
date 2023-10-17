#ifndef CAT_H
#define CAT_H

#include "Item.h"

class Cat : public Item {
 protected:
  bool isWithPlayer;

 public:
  Cat();
  Cat(Vector position, Vector dimensions, std::string type,
         std::string description);
//   void use(Player* player);
//   void render(sf::RenderWindow &window);
//   void update();
//   bool getIsWithPlayer();
};

#endif