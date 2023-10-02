#ifndef ITEM_INCLUDE
#define ITEM_INCLUDE

#include "RenderedObject.h"

class Item : public RenderedObject {
 protected:
  string description;

 public:
  Item();
  virtual void use();
  virtual void render();
  virtual void update();
};

#endif