#ifndef ITEM_INCLUDE
#define ITEM_INCLUDE

#include "Renderable.hpp"
#include "Obstacle.hpp"

class Item : public Renderable {
protected:
     std::string description;
     sf::Sprite* sprite;

public:
     Item();
     Item(Vector position, Vector dimensions);

     void update();
     virtual int getValue();
     bool isInObstacle(Obstacle* obstacles, int obstacles_num);
};

#endif