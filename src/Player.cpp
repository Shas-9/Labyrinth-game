#include "Player.h"

// Default constructor for player does nothing (Environment required)
Player::Player() {}

Player::Player(Vector position, string type, string movement_animation,
               int movement_speed, int health, int attack_damage,
               string attack_animation, string death_animation,
               Environment* environment)
    : Entity(position, type, movement_animation, movement_speed, health,
             attack_damage, attack_animation, death_animation),
      environment(environment) {}

// Move player up
void Player::moveUp() {
  this->position.set(this->position.getX(),this->position.getY() - movement_speed);
}

// Move player down
void Player::moveDown() {
  this->position.set(this->position.getX(),this->position.getY() + movement_speed);
}

// Move player right
void Player::moveRight() {
  this->position.set(this->position.getX() + movement_speed,this->position.getY());
}

// Move player left
void Player::moveLeft() {
  this->position.set(this->position.getX() - movement_speed,this->position.getY());
}

// Attack with weapon if player has one, otherwise attack with fists
// void Player::attack() {
//   Enemy *enemies_array = this->environment->getEnemies();

//   if (this->current_item != nullptr) {
//     for (int i = 0; i < this->environment->getEnemiesNum(); i++) {
//       if (this->collidingWith(&enemies_array[i])) {
//         enemies_array[i].takeDamage(this->current_item.use(this));
//       }
//     }
//     else if (this->current_item == Null) {
//       for (int i = 0; i < this->environment->getEnemiesNum(); i++) {
//         if (this->collidingWith(enemies_array[i])) {
//           enemies_array[i].takeDamage(this->attack_damage);
//         }
//       }
//     }
//   }
// }


// Pick up item if player is near one
void Player::pickUpItem(Item* item) {
  if (this->getNearbyItem() != NULL) {
    // this->current_item = item;
  }
}

// Drop item if player has one
// void Player::dropItem() {
//   if (this->current_item != NULL) {
//     this->current_item = NULL;
//   }
// }

// Get player's score
int Player::getScore() {
  return this->score;
}

// Get nearby item if there is one
Item* Player::getNearbyItem() {
  Item* items_array = this->environment->getItems();
  
  for (int i = 0; i < this->environment->getItemsNum(); i++) {
    if (this->collidingWith(&items_array[i])) {
      //  if (items_array[i].getType() == "weapon") {
      //    // items_array[i].pickUp();
      //    if (this->current_item != NULL) {
      //      // this->current_item.drop();
      //    }
      //    return &items_array[i];
      //  }
       if (items_array[i].getType() == "potion") {
         items_array[i].use(this);
         return NULL;
       } 
       else {
         return NULL;
       }
    }
  }
}

// Render player
void Player::render(sf::RenderWindow &window) {
  window.draw(*this->rectangle);
}
