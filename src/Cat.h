#ifndef CAT_H
#define CAT_H

#include "Item.h"

class Cat : public Item {
protected:
       bool isWithPlayer;

public:
       Cat();
       Cat(
              Vector position,
              sf::Texture* cat_texture
       );
};

#endif