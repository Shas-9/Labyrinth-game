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