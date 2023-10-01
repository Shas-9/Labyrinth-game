#ifndef ENTITY_INCLDUE
#define ENTITY_INCLUDE

#include <string>
using namespace std;

#include "RenderedObject.h"
#include "Vector.h"

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
  void changePosition(Vector position);
};

#endif