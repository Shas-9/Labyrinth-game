#include "Entity.h"

// Default constructor
Entity::Entity() {}

// Constructor for entity that sets the properties
Entity::Entity(
  Vector position,
  Vector dimensions,
  string type,
  int movement_speed,
  int health,
  int attack_damage,
  Obstacle* obstacles,
  int obstacles_num
) : RenderedObject(position, dimensions, type),
movement_speed(movement_speed),
health(health),
attack_damage(attack_damage) {
  this->max_health = health;

  // Obstacles awareness
  this->obstacles = obstacles;
  this->obstacles_num = obstacles_num;

  // Movement
  this->moving_left = false;
  this->moving_right = false;
  this->moving_up = false;
  this->moving_down = false;

  // Loading textures
  this->current_frames_index = 0;
  this->current_animation_frame = 0;
  this->sprite = new sf::Sprite();
}

// Checks whether the entity can move or not by 
// detecting whether it's inside any of the obstacles in the map or not
bool Entity::canMove() {
  // Loop over all obstacles and check if entity is running into them
  for (int i = 0; i < this->obstacles_num; i++) {
    if (this->isCollidingWithObject(&(this->obstacles[i]))) {
      // If entity is colliding with an obstacle, go back to old position.
      return false;
    }
  }
  // If no obstacles is deetected to be colliding with entity return true
  return true;
}

// Move entity up
void Entity::moveUp() {
  // Save the old position of the entity before doing the movement
  Vector old_position = this->position;
  // Move the entity to new position
  this->position.set(this->position.getX(), this->position.getY() - movement_speed);

  // Check if entity can move (to know where it's in an obstacle or not)
  if (!this->canMove()) {
    // If entity moved into an obstacle, move it back to the old position
    // to prevent walking into the obstacle
    this->position.set(this->position.getX(), old_position.getY());
  }
}

// Move entity down
void Entity::moveDown() {
  // Save the old position of the entity before doing the movement
  Vector old_position = this->position;
  // Move the entity to new position
  this->position.set(this->position.getX(), this->position.getY() + movement_speed);

  // Check if entity can move (to know where it's in an obstacle or not)
  if (!this->canMove()) {
    // If entity moved into an obstacle, move it back to the old position
    // to prevent walking into the obstacle
    this->position.set(this->position.getX(), old_position.getY());
  }
}

// Move entity right
void Entity::moveRight() {
  // Save the old position of the entity before doing the movement
  Vector old_position = this->position;
  // Move the entity to new position
  this->position.set(this->position.getX() + movement_speed, this->position.getY());

  // Check if entity can move (to know where it's in an obstacle or not)
  if (!this->canMove()) {
    // If entity moved into an obstacle, move it back to the old position
    // to prevent walking into the obstacle
    this->position.set(old_position.getX(), this->position.getY());
  }
}

// Move entity left
void Entity::moveLeft() {
  // Save the old position of the entity before doing the movement
  Vector old_position = this->position;
  // Move the entity to new position
  this->position.set(this->position.getX() - movement_speed, this->position.getY());

  // Check if entity can move (to know where it's in an obstacle or not)
  if (!this->canMove()) {
    // If entity moved into an obstacle, move it back to the old position
    // to prevent walking into the obstacle
    this->position.set(old_position.getX(), this->position.getY());
  }
}

// Set whether the player is moving in a given direction or not
// 0 = left
// 1 = right
// 2 = up
// 3 = down
void Entity::setMovementDirection(int direction, bool is_moving) {
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
int Entity::getMovementDirection(int direction) {
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
    return 0;
    break;
  }
}

// Render the entity (also handles movement animation)
void Entity::render(sf::RenderWindow *window, Vector camera_position) {
  // Use the utility function "frames handles" to handle frames of walking
  Utility::frames_handler(
    this->sprite,
    &this->current_frames_index,
    &this->current_animation_frame,
    walking_frames,
    moving_left,
    moving_right,
    moving_up,
    moving_down,
    20
  );

  // Sets the new position for the sprite of the entity and renders it on the screen
  this->sprite->setPosition(
    this->position.getX() - camera_position.getX(),
    this->position.getY() - camera_position.getY()
  );
  window->draw(*this->sprite);
}

// Get the health of the entity as a percentage
int Entity::getHealth() {
  return (((double)this->health / this->max_health) * 100);
}

// Make entity lose health (resitricted to zero)
void Entity::loseHealth(int damage) {
  if (damage > 0) {
    if ((this->health - damage) < 0) {
      this->health = 0;
    } else {
      this->health = this->health - damage;
    }
  }
}

// Make entity gain health (restricted to max_health)
void Entity::gainHealth(int extra_health) {
  if (extra_health > 0) {
    if ((this->health + extra_health) > this->max_health) {
      this->health = this->max_health;
    } else {
      this->health += extra_health;
    }
  }
}

void Entity::addSpeed(int speed){
  this->movement_speed += speed;
}

// Get the attack_damage of the entity
int Entity::getAttackDamage() {
  return this->attack_damage;
}