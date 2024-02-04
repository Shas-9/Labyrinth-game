#ifndef FASTPOTION_H
#define FASTPOTION_H

#include "Item.h"

class FastPotion : public Item {
protected:
       int speedBoost;

public:
       FastPotion();
       FastPotion(
              Vector position,
              sf::Texture* potion_texture
       );
};

#endif