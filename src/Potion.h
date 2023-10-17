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
              std::string type,
              std::string description,
              int health_regen,
              sf::Texture* potion_texture
       );
       int getValue();
       int getHealthRegen();
};

#endif