#ifndef ITEM_INCLUDE
#define ITEM_INCLUDE

#include "RenderedObject.h"
#include "Obstacle.h"

class Item : public RenderedObject {
protected:
     std::string description;
     sf::Sprite* sprite;
     double scale;

public:
     Item();
     Item(Vector position, Vector dimensions, std::string type, std::string description);

     void update();
     void render(std::shared_ptr<Camera> cam);
     std::string getType();
     virtual int getValue();
     bool isInObstacle(Obstacle* obstacles, int obstacles_num);
};

#endif