#include "Game.h"

// Default Game constructer does nothing (window object required)
Game::Game() {}

Game::Game(sf::RenderWindow *window_ptr, sf::Event* event_ptr) {
  Utility* util = new Utility();
  util->loadObstacleTexture();
  util->loadGroundTexture();
  util->loadPlayerTexture();

  this->window_ptr = window_ptr;
  this->environment = new Environment(
    util->getObstacleTexture(),
    util->getObstacleTexture(),
    util->getObstacleTexture()
  );
  this->isGamePaused = false;
  this->isGameOver = false;

  // Create the player object
  this->player = Player(
    Vector(MAZE_BOX_THICKNESS + 10, MAZE_BOX_THICKNESS + 10),
    Vector(140, 180),
    "player",
    "movement_animation",
    4,
    100,
    10,
    "attack_animation",
    "death_animation",
    this->environment,
    util->getPlayerTexture()
  );

  this->event_ptr = event_ptr;

  Button pause_button("Pause", Vector(780, 20), Vector(200, 50), sf::Color(136, 149, 168), sf::Color::Black, 24);

  // Loading ground textures
  sf::IntRect* rectSourceSprite = new sf::IntRect(0, 0, 60000, 60000);
  sf::Sprite* ground_sprite = new sf::Sprite();
  ground_sprite->setTexture(*util->getGroundTexture());
  ground_sprite->setTextureRect(*rectSourceSprite);
  ground_sprite->scale(sf::Vector2f(3, 3));

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
        //   if ((pause_button.isMouseOver(*this->window_ptr))) {
        //     std::cout << "Menu button pressed" << std::endl;
        //     // menu_button_pressed = true;
        //     return;
        //   }
        //   break;

        // case sf::Event::MouseMoved:
        //   if (pause_button.isMouseOver(*this->window_ptr)) {
        //     pause_button.setBackToColor(sf::Color::Red);
        //   } else {
        //     pause_button.setBackToColor(sf::Color::Blue);
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

    // Render the ground
    ground_sprite->setPosition(sf::Vector2f(-player.getPosition().getX() + 500, -player.getPosition().getY() + 400));
    this->window_ptr->draw(*ground_sprite);

    // Render the player
    this->player.render(this->window_ptr);

    // Render all obstacles/walls of the cave
    for (int i = 0; i < this->environment->getObstaclesNum(); i++) {
      this->environment->getObstacles()[i].render(this->window_ptr, player.getPosition());
    }

    // Render the pause button
    pause_button.drawButton(*this->window_ptr);

    // Display the current frame
    (*this->window_ptr).display();

  }
}

void Game::renderAll() {

}

void Game::updateAll() {
  if (!this->isGamePaused) {
  }
}