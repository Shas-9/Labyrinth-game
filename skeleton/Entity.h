#ifndef ENTITY_INCLUDE
#define ENTITY_INCLUDE

#include <string>
using namespace std;

#include "RenderedObject.h"

class Entity : public RenderedObject {
 protected:
  string movement_animation;
  int movement_speed;
  int health;
  int attack_damage;
  string attack_animation;
  string death_animation;

 public:
  Entity();
  Entity(Vector position, string type, string movement_animation,
         int movement_speed, int health, int attack_damage,
         string attack_animation, string death_animation);
  void changePosition(Vector position);
  void update();
};

#endif