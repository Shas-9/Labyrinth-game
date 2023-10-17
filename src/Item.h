#ifndef ITEM_INCLUDE
#define ITEM_INCLUDE

#include "RenderedObject.h"
#include "Obstacle.h"

class Item : public RenderedObject {
protected:
     std::string description;
     sf::Sprite* sprite;

public:
     Item();
     Item(Vector position, Vector dimensions, std::string type, std::string description);

     void update();
     void render(sf::RenderWindow *window, Vector camera_position);
     std::string getType();
     bool isInObstacle(Obstacle* obstacles, int obstacles_num);
};

#endif