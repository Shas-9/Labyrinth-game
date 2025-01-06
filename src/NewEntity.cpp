#include "NewEntity.h"
#include "singleton/Utility.h"

// Default constructor
NewEntity::NewEntity() {}

// Constructor for entity that sets the properties
NewEntity::NewEntity(
  Vector position,
  Vector dimensions,
  int movement_speed,
  int health,
  int attack_damage,
  std::string texture_location,
  Vector texture_dimensions
) : movement_speed(movement_speed), health(health), attack_damage(attack_damage) {
  this->max_health = health;

  // Movement
  this->moving_left = false;
  this->moving_right = false;
  this->moving_up = false;
  this->moving_down = false;

  std::shared_ptr<AnimController> anim_cont = std::make_shared<AnimController>();
  anim_cont->addRow(texture_dimensions, 4, "walking_down");
  anim_cont->addRow(texture_dimensions, 4, "walking_up");
  anim_cont->addRow(texture_dimensions, 4, "walking_left");
  anim_cont->addRow(texture_dimensions, 4, "walking_right");
  
  this->renderable = Renderable(position, dimensions, "rect");
  this->renderable.setTexture(texture_location);
  // this->renderable.registerStaticSprite(Vector(64, 64));
  this->renderable.registerAnimController(anim_cont);
  this->renderable.getAnimController()->setActivity("walking_down");
}

// Checks whether the entity can move or not by 
// detecting whether it's inside any of the obstacles in the map or not
bool NewEntity::canMove() {
  // Loop over all obstacles and check if entity is running into them
  // for (int i = 0; i < this->obstacles_num; i++) {
  //   if (this->isCollidingWithObject(&(this->obstacles[i]))) {
  //     // If entity is colliding with an obstacle, go back to old position.
  //     return false;
  //   }
  // }
  // If no obstacles is deetected to be colliding with entity return true
  return true;
}

// Move entity up
void NewEntity::moveUp() {
  // Save the old position of the entity before doing the movement
  Vector old_position = this->renderable.getPosition();
  // Move the entity to new position
  this->renderable.setPosition(Vector(this->renderable.getPosition().getX(), this->renderable.getPosition().getY() - (movement_speed * UTIL_CLASS.getTimeFactor())));

  // Check if entity can move (to know where it's in an obstacle or not)
  if (!this->canMove()) {
    // If entity moved into an obstacle, move it back to the old position
    // to prevent walking into the obstacle
    this->renderable.setPosition(Vector(this->renderable.getPosition().getX(), old_position.getY()));
  }
}

// Move entity down
void NewEntity::moveDown() {
  // Save the old position of the entity before doing the movement
  Vector old_position = this->renderable.getPosition();
  // Move the entity to new position
  this->renderable.setPosition(Vector(this->renderable.getPosition().getX(), this->renderable.getPosition().getY() + (movement_speed * UTIL_CLASS.getTimeFactor())));

  // Check if entity can move (to know where it's in an obstacle or not)
  if (!this->canMove()) {
    // If entity moved into an obstacle, move it back to the old position
    // to prevent walking into the obstacle
    this->renderable.setPosition(Vector(this->renderable.getPosition().getX(), old_position.getY()));
  }
}

// Move entity right
void NewEntity::moveRight() {
  // Save the old position of the entity before doing the movement
  Vector old_position = this->renderable.getPosition();
  // Move the entity to new position
  this->renderable.setPosition(Vector(this->renderable.getPosition().getX() + (movement_speed * UTIL_CLASS.getTimeFactor()), this->renderable.getPosition().getY()));

  // Check if entity can move (to know where it's in an obstacle or not)
  if (!this->canMove()) {
    // If entity moved into an obstacle, move it back to the old position
    // to prevent walking into the obstacle
    this->renderable.setPosition(Vector(old_position.getX(), this->renderable.getPosition().getY()));
  }
}

// Move entity left
void NewEntity::moveLeft() {
  // Save the old position of the entity before doing the movement
  Vector old_position = this->renderable.getPosition();
  // Move the entity to new position
  this->renderable.setPosition(Vector(this->renderable.getPosition().getX() - (movement_speed * UTIL_CLASS.getTimeFactor()), this->renderable.getPosition().getY()));

  // Check if entity can move (to know where it's in an obstacle or not)
  if (!this->canMove()) {
    // If entity moved into an obstacle, move it back to the old position
    // to prevent walking into the obstacle
    this->renderable.setPosition(Vector(old_position.getX(), this->renderable.getPosition().getY()));
  }
}

// Set whether the player is moving in a given direction or not
// 0 = left
// 1 = right
// 2 = up
// 3 = down
void NewEntity::setMovementDirection(int direction, bool is_moving) {
  switch (direction) {
  case 0:
    this->moving_left = is_moving;
    break;
  case 1:
    this->moving_right = is_moving;
    break;
  case 2:
    this->moving_up = is_moving;
    break;
  case 3:
    this->moving_down = is_moving;
    break;

  default:
    break;
  }
}

// Get whether the entity is moving in a current direction or not
// 0 = left
// 1 = right
// 2 = up
// 3 = down
bool NewEntity::getMovementDirection(int direction) {
  switch (direction) {
  case 0:
    return this->moving_left;
    break;
  case 1:
    return this->moving_right;
    break;
  case 2:
    return this->moving_up;
    break;
  case 3:
    return this->moving_down;
    break;

  default:
    return false;
    break;
  }
}

// Render the entity (also handles movement animation)
void NewEntity::render(std::shared_ptr<Camera> cam) {
  // this->renderable.render(cam);
  if (this->moving_down) this->renderable.getAnimController()->setActivity("walking_down");
  if (this->moving_up) this->renderable.getAnimController()->setActivity("walking_up");
  if (this->moving_left) this->renderable.getAnimController()->setActivity("walking_left");
  if (this->moving_right) this->renderable.getAnimController()->setActivity("walking_right");
  this->renderable.render(cam);
}

// Get the health of the entity as a percentage
int NewEntity::getHealth() {
  return (((double)this->health / this->max_health) * 100);
}

// Make entity lose health (resitricted to zero)
void NewEntity::loseHealth(int damage) {
  if (damage > 0) {
    if ((this->health - damage) < 0) {
      this->health = 0;
    } else {
      this->health = this->health - damage;
    }
  }
}

// Make entity gain health (restricted to max_health)
void NewEntity::gainHealth(int extra_health) {
  if (extra_health > 0) {
    if ((this->health + extra_health) > this->max_health) {
      this->health = this->max_health;
    } else {
      this->health += extra_health;
    }
  }
}

// Get the attack_damage of the entity
int NewEntity::getAttackDamage() {
  return this->attack_damage;
}

void NewEntity::movementUpdate() {
  if (this->getMovementDirection(0)) this->moveLeft();
  if (this->getMovementDirection(1)) this->moveRight();
  if (this->getMovementDirection(2)) this->moveUp();
  if (this->getMovementDirection(3)) this->moveDown();
}

void NewEntity::update() {
  if (this->moving_down || this->moving_up || this->moving_left || this->moving_right) {
    this->renderable.getAnimController()->tempResumeFrames();
    this->renderable.getAnimController()->updateFrame(140, "repeat");
  } else this->renderable.getAnimController()->tempResetFrames();

  this->movementUpdate();
  // class-specific behavior
  this->behaviorUpdate();
}

Vector NewEntity::getPosition() { return this->renderable.getPosition(); }
Vector NewEntity::getDimensions() { return this->renderable.getDimensions(); }