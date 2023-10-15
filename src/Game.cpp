#include "Game.h"

// Default Game constructer does nothing (window object required)
Game::Game() {}

Game::Game(sf::RenderWindow *window_ptr) {
  this->window_ptr = window_ptr;
  this->environment = new Environment();
  this->isGamePaused = false;
}

void Game::updateAll() {
  if (!this->isGamePaused) {
    }
}