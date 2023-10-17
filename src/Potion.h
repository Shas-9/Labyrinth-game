#ifndef POTION_H
#define POTION_H

#include "Item.h"

class Potion : public Item {
protected:
       int health_regen;

public:
       Potion();
       Potion(
              Vector position,
              sf::Texture* potion_texture
       );
};

#endif