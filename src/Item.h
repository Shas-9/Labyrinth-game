#ifndef ITEM_INCLUDE
#define ITEM_INCLUDE

#include "RenderedObject.h"
class Player;

class Item : public RenderedObject {
protected:
     std::string description;

public:
     Item();
     Item(Vector position, Vector dimensions, std::string type, std::string description);

     virtual void use(Player* player);
     virtual void update() override;
     std::string getType();
};

#endif