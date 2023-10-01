#ifndef ITEM_INCLDUE
#define ITEM_INCLUDE

#include "RenderedObject.h"

class Item : public RenderedObject {
 protected:
  string description;

 public:
  Item();
  virtual void use() = 0;
};

#endif