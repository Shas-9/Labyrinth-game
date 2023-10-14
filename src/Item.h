#ifndef ITEM_INCLUDE
#define ITEM_INCLUDE

#include "RenderedObject.h"
#include "Player.h"

class Item : public RenderedObject {
 protected:
  std::string description;

 public:
  Item();
  Item(Vector position, Vector dimensions, std::string type,
       std::string description);
  virtual void use(Player* player);
  virtual void render();
  virtual void update();

  std::string getType();
};

#endif