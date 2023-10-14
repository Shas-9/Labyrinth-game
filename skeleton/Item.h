#ifndef ITEM_INCLUDE
#define ITEM_INCLUDE

#include "RenderedObject.h"

class Item : public RenderedObject {
 protected:
  std::string description;

 public:
  Item();
  virtual void use();
  virtual void render();
  virtual void update();

  std::string getType();
};

#endif