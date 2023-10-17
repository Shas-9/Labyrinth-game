#include "Entity.h"

Entity::Entity() {}

// The constructor for the object
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

bool Entity::canMove() {
  // Loop over all obstacles and check if player is running into them
  for (int i = 0; i < this->obstacles_num; i++) {
    if (this->collidingWith(&(this->obstacles[i]))) {
      // If player is colliding with an obstacle, go back to old position.
      return false;
    }
  }
  return true;
}

// Move player up
void Entity::moveUp() {
  Vector old_position = this->position;
  this->position.set(this->position.getX(), this->position.getY() - movement_speed);

  if (!this->canMove()) {
    this->position.set(this->position.getX(), old_position.getY());
  }
}

// Move player down
void Entity::moveDown() {
  Vector old_position = this->position;
  this->position.set(this->position.getX(), this->position.getY() + movement_speed);

  if (!this->canMove()) {
    this->position.set(this->position.getX(), old_position.getY());
  }
}

// Move player right
void Entity::moveRight() {
  Vector old_position = this->position;
  this->position.set(this->position.getX() + movement_speed, this->position.getY());

  if (!this->canMove()) {
    this->position.set(old_position.getX(), this->position.getY());
  }
}

// Move player left
void Entity::moveLeft() {
  // Save old position
  Vector old_position = this->position;
  // Move to new position
  this->position.set(this->position.getX() - movement_speed, this->position.getY());

  if (!this->canMove()) {
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

void Entity::render(sf::RenderWindow *window, Vector camera_position) {
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

  this->sprite->setPosition(
    this->position.getX() - camera_position.getX(),
    this->position.getY() - camera_position.getY()
  );
  window->draw(*this->sprite);

}

int Entity::getHealth() {
  return (((double)this->health / this->max_health) * 100);
}

void Entity::loseHealth(int lost_health) {
  if ((this->health + lost_health) < 0) {
    this->health = 0;
    cout << "huh" << endl;
  } else {
    this->health = this->health + lost_health;
  }
}

void Entity::gainHealth(int extra_health) {
  if ((this->health + extra_health) > this->max_health) {
    this->health = this->max_health;
  } else {
    this->health += extra_health;
  }
}