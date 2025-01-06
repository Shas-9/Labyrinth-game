#ifndef NEW_ENTITY_INCLUDE
#define NEW_ENTITY_INCLUDE

#include "Renderable.h"
#include <string>

class NewEntity {
protected:
  // Movement
  bool moving_left;
  bool moving_right;
  bool moving_up;
  bool moving_down;
  int movement_speed;

  // Animation
  Renderable renderable;

  // Properties
  int health;
  int max_health;
  int attack_damage;

public:
  NewEntity();
  NewEntity(Vector position, Vector dimensions, int movement_speed, int health, int attack_damage, std::string texture_location,
  Vector texture_dimensions);

  Vector getPosition();
  Vector getDimensions();

  int getHealth();
  void loseHealth(int lost_health);
  void gainHealth(int extra_health);

  void moveUp();
  void moveDown();
  void moveRight();
  void moveLeft();

  void setMovementDirection(int direction, bool is_moving);
  bool getMovementDirection(int direction);
  int getAttackDamage();

  bool canMove();

  void movementUpdate();
  virtual void behaviorUpdate() = 0;
  void update();
  void render(std::shared_ptr<Camera> cam);
};

#endif