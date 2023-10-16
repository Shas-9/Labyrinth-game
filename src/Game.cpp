#include "Game.h"
#include "Button.h"
// Default Game constructer does nothing (window object required)
Game::Game() {}

Game::Game(sf::RenderWindow *window_ptr, sf::Event* event_ptr) {
  this->window_ptr = window_ptr;
  this->environment = new Environment();
  this->isGamePaused = false;
  this->isGameOver = false;

  // Create the player object
  this->player = Player(
    Vector(300, 300),
    Vector(50, 50),
    "player",
    "movement_animation",
    2,
    100,
    10,
    "attack_animation",
    "death_animation",
    this->environment
  );

  this->event_ptr = event_ptr;

  Button menu("Pause", Vector(780, 20), Vector(200, 50), sf::Color(136, 149, 168), sf::Color::Black, 24);
  Obstacle *test_obs = new Obstacle(Vector(0, 0), "obstacle", Vector(30, 200));

  // Screen loop
  while ((*this->window_ptr).isOpen()) {

    // Event loop
    while ((*this->window_ptr).pollEvent((*this->event_ptr))) {
      switch ((*this->event_ptr).type) {
      case sf::Event::Closed:
        (*this->window_ptr).close();
        break;

      case sf::Event::KeyPressed:
        if ((*this->event_ptr).key.code == sf::Keyboard::A) {
          this->player.setMovementDirection(0, true);
        }
        if ((*this->event_ptr).key.code == sf::Keyboard::D) {
          this->player.setMovementDirection(1, true);
        }
        if ((*this->event_ptr).key.code == sf::Keyboard::W) {
          this->player.setMovementDirection(2, true);
        }
        if ((*this->event_ptr).key.code == sf::Keyboard::S) {
          this->player.setMovementDirection(3, true);
        }
        break;

      case sf::Event::KeyReleased:
        if ((*this->event_ptr).key.code == sf::Keyboard::A) {
          this->player.setMovementDirection(0, false);
        }
        if ((*this->event_ptr).key.code == sf::Keyboard::D) {
          this->player.setMovementDirection(1, false);
        }
        if ((*this->event_ptr).key.code == sf::Keyboard::W) {
          this->player.setMovementDirection(2, false);
        }
        if ((*this->event_ptr).key.code == sf::Keyboard::S) {
          this->player.setMovementDirection(3, false);
        }
        break;

        // case sf::Event::MouseButtonPressed:
        //   if ((menu.isMouseOver(*this->window_ptr))) {
        //     std::cout << "Menu button pressed" << std::endl;
        //     // menu_button_pressed = true;
        //     return;
        //   }
        //   break;

        // case sf::Event::MouseMoved:
        //   if (menu.isMouseOver(*this->window_ptr)) {
        //     menu.setBackToColor(sf::Color::Red);
        //   } else {
        //     menu.setBackToColor(sf::Color::Blue);
        //   }
        //   break;
      }
    }

    if (this->player.getMovementDirection(0)) {
      this->player.moveLeft();
    }
    if (this->player.getMovementDirection(1)) {
      this->player.moveRight();
    }
    if (this->player.getMovementDirection(2)) {
      this->player.moveUp();
    }
    if (this->player.getMovementDirection(3)) {
      this->player.moveDown();
    }

    (*this->window_ptr).clear();

    this->player.render(this->window_ptr);
    
    test_obs->render(this->window_ptr, this->player.getPosition());
    // Display on the screen
    for (int i = 0; i < this->environment->getObstaclesNum(); i++) {
      this->environment->getObstacles()[i].render(this->window_ptr, player.getPosition());
    }

    menu.drawButton(*this->window_ptr);
    (*this->window_ptr).display();
  }
}

void Game::renderAll() {

}

void Game::updateAll() {
  if (!this->isGamePaused) {
  }
}