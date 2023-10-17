#include "Game.h"

#define MOUSE_OVER_COLOR sf::Color (59, 5, 44)
#define PAUSE_BUTTON_COLOR sf::Color (22, 30, 43)
#define QUIT_BUTTON_COLOR sf::Color (74, 74, 46)
#define BUTTON_TEXT_SIZE int (40)
#define BUTTON_SIZE Vector (250, 110)

// Default Game constructer does nothing (window object required)
Game::Game() {}


Game::Game(sf::RenderWindow *window_ptr, sf::Event* event_ptr, Vector screen_dimensions, sf::Clock* clock) {
  srand(time(NULL));

  Utility* util = new Utility();
  util->loadObstacleTexture();
  util->loadGroundTexture();
  util->loadPlayerTexture();
  util->loadIronSpiderTexture();
  util->loadPotionTexture();

  this->window_ptr = window_ptr;
  this->environment = new Environment(
    util->getObstacleTexture(),
    util->getPotionTexture(),
    util->getIronSpiderTexture()
  );
  this->isGamePaused = false;
  this->isGameOver = false;

  // Create the player object
  this->player = Player(
    Vector(MAZE_BOX_THICKNESS + 10, MAZE_BOX_THICKNESS + 10),
    Vector(140/2, 180/2),
    "player",
    4,
    9000,
    10,
    this->environment,
    util->getPlayerTexture()
  );

  this->event_ptr = event_ptr;


  Button pause_button("Pause Game", Vector(1570, 20), Vector(270, 100), PAUSE_BUTTON_COLOR, sf::Color::White,
                      BUTTON_TEXT_SIZE, 10);

  std::string hp_string = "HP: ";
  Button hp_text(hp_string, Vector(100, 50), Vector(100, 30), sf::Color(0, 0, 0, 0), sf::Color::White, 44, 5);
  hp_text.setCustomFont("fonts/MouldyCheese.ttf");

  std::string time_string = "Time: ";
  Button time_text(time_string, Vector(900, 50), Vector(100, 30), sf::Color(0,0,0,0), sf::Color::White, 44, 5);
  time_text.setCustomFont("fonts/MouldyCheese.ttf");

  // Loading ground textures
  sf::IntRect* rectSourceSprite = new sf::IntRect(0, 0, MAP_BOUNDS/3, MAP_BOUNDS/3);
  sf::Sprite* ground_sprite = new sf::Sprite();
  ground_sprite->setTexture(*util->getGroundTexture());
  ground_sprite->setTextureRect(*rectSourceSprite);
  ground_sprite->scale(sf::Vector2f(3, 3));

  int time_elapsed = 0;

  // Screen loop
  while ((*this->window_ptr).isOpen() && !(this->isGameOver)) {

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
        if ((*this->event_ptr).key.code == sf::Keyboard::Escape) {
          time_elapsed = clock->getElapsedTime().asSeconds();
          bool resume_button_pressed = false;

          while (!(resume_button_pressed)) {
            resume_button_pressed = this->pauseScreen();
          }
          clock->restart();
        }
        break;

      case sf::Event::MouseMoved:
        if (pause_button.isMouseOver(*this->window_ptr)) {
          pause_button.setBackToColor(MOUSE_OVER_COLOR);
        } else {
          pause_button.setBackToColor(PAUSE_BUTTON_COLOR);
        }
        break;

      case sf::Event::MouseButtonPressed:
        if ((pause_button.isMouseOver(*this->window_ptr))) {
          std::cout << "Pause button pressed" << std::endl;
          time_elapsed = clock->getElapsedTime().asSeconds();
          bool resume_button_pressed = false;

          while (!(resume_button_pressed)) {
            resume_button_pressed = this->pauseScreen();
          }
        clock->restart();
        }

        break;
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

    // Calculate the camera position for all rendered objects
    Vector camera_position = Vector(
      player.getPosition().getX() - ((screen_dimensions.getX() - player.getDimensions().getX()) / 2),
      player.getPosition().getY() - ((screen_dimensions.getY() - player.getDimensions().getY()) / 2)
    );

    // Update the ground's position relative to the player
    ground_sprite->setPosition(
      sf::Vector2f(
        -camera_position.getX(),
        -camera_position.getY()
      )
    );

    // Render the ground
    this->window_ptr->draw(*ground_sprite);

    // Render all obstacles/walls of the cave
    for (int i = 0; i < this->environment->getObstaclesNum(); i++) {
      this->environment->getObstacles()[i].render(this->window_ptr, camera_position);
    }

    // Render and update all enemies
    for (int i = 0; i < this->environment->getEnemiesNum(); i++) {
      if (this->environment->getEnemies()[i].getMovementDirection(0)) {
        this->environment->getEnemies()[i].moveLeft();
      }
      if (this->environment->getEnemies()[i].getMovementDirection(1)) {
        this->environment->getEnemies()[i].moveRight();
      }
      if (this->environment->getEnemies()[i].getMovementDirection(2)) {
        this->environment->getEnemies()[i].moveUp();
      }
      if (this->environment->getEnemies()[i].getMovementDirection(3)) {
        this->environment->getEnemies()[i].moveDown();
      }

      if (this->environment->getEnemies()[i].isCollidingWithObject(&this->player)) {
        player.loseHealth(this->environment->getEnemies()[i].getAttackDamage());
      }

      this->environment->getEnemies()[i].render(this->window_ptr, camera_position);
      this->environment->getEnemies()[i].update();
    }

    // Render and update all enemies
    for (int i = 0; i < this->environment->getItemsNum(); i++) {
      if (this->environment->getItems()[i].isCollidingWithObject(&this->player)) {
        // Use item
        if (this->environment->getItems()[i].getType() == "health") {
          this->player.gainHealth(this->environment->getItems()[i].getValue());
        }
        // player.gainHealth(this->environment->getItems()[i]());
      }

      this->environment->getItems()[i].render(this->window_ptr, camera_position);
    }

    // Render the player
    this->player.render(this->window_ptr, screen_dimensions);

    // Render the pause button
    pause_button.drawButton(*this->window_ptr);

    // Render the hp text
    hp_string = "Health: " + std::to_string(this->player.getHealth());
    hp_text.setString(hp_string);
    hp_text.drawButton(*this->window_ptr);

    // Render the time text
    time_string = "Time: " + std::to_string((int)clock->getElapsedTime().asSeconds() + time_elapsed) + "s";
    time_text.setString(time_string);
    time_text.drawButton(*this->window_ptr);

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

bool Game::confirmationScreen() {
  sf::Texture texture;
  texture.loadFromFile("images/UI.png");
  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setTextureRect(sf::IntRect(0, 0, (*this->window_ptr).getSize().x, (*this->window_ptr).getSize().y));

  sf::Font font;
  font.loadFromFile("fonts/MouldyCheese.ttf");
  sf::Text quit_text;
  quit_text.setFont(font);
  quit_text.setString("Are you sure you want to quit?");
  quit_text.setCharacterSize(46);
  quit_text.setFillColor(sf::Color::White);
  quit_text.setPosition(sf::Vector2f(580, 650));

  Button yes_button("Yes", Vector(300, 800), BUTTON_SIZE, PAUSE_BUTTON_COLOR, sf::Color::White, BUTTON_TEXT_SIZE, 10);
  Button no_button("No", Vector(1300, 800), BUTTON_SIZE, QUIT_BUTTON_COLOR, sf::Color::White, BUTTON_TEXT_SIZE, 10);

  // Screen loop
  while ((*this->window_ptr).isOpen()) {

    // Event loop
    while ((*this->window_ptr).pollEvent((*this->event_ptr))) {
      switch ((*this->event_ptr).type) {
      case sf::Event::Closed:
        (*this->window_ptr).close();
        break;

      case sf::Event::MouseMoved:
        if (yes_button.isMouseOver(*this->window_ptr)) {
          yes_button.setBackToColor(MOUSE_OVER_COLOR);
        } else {
          yes_button.setBackToColor(PAUSE_BUTTON_COLOR);
        }

        if (no_button.isMouseOver(*this->window_ptr)) {
          no_button.setBackToColor(MOUSE_OVER_COLOR);
        } else {
          no_button.setBackToColor(QUIT_BUTTON_COLOR);
        }
        break;

      case sf::Event::MouseButtonPressed:
        if ((yes_button.isMouseOver(*this->window_ptr))) {
          std::cout << "Yes button pressed" << std::endl;
          this->isGameOver = true;
          return true;
        }

        if ((no_button.isMouseOver(*this->window_ptr))) {
          std::cout << "No button pressed" << std::endl;
          return false;
        }
      }
    }

    (*this->window_ptr).clear();

    (*this->window_ptr).draw(sprite);
    yes_button.drawButton(*this->window_ptr);
    no_button.drawButton(*this->window_ptr);
    (*this->window_ptr).draw(quit_text);

    (*this->window_ptr).display();

  }
}

bool Game::pauseScreen() {
  sf::Texture texture;
  texture.loadFromFile("images/UI.png");
  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setTextureRect(sf::IntRect(0, 0, (*this->window_ptr).getSize().x, (*this->window_ptr).getSize().y));

  sf::Font font;
  font.loadFromFile("fonts/MouldyCheese.ttf");
  sf::Font cat_font;
  cat_font.loadFromFile("fonts/cat_font.ttf");

  sf::Text pause_text;
  pause_text.setFont(cat_font);
  pause_text.setString("Game Paused");
  pause_text.setCharacterSize(130);
  pause_text.setFillColor(sf::Color::White);
  pause_text.setPosition(sf::Vector2f(500, 350));

  sf::Text resume_text;
  resume_text.setFont(font);
  resume_text.setString("All progress will be lost if you quit");
  resume_text.setCharacterSize(46);
  resume_text.setFillColor(sf::Color::White);
  resume_text.setPosition(sf::Vector2f(580, 650));

  Button resume_button("Resume", Vector(300, 800), BUTTON_SIZE, PAUSE_BUTTON_COLOR, sf::Color::White, BUTTON_TEXT_SIZE, 10);
  Button quit_game_button("Quit Game", Vector(1300, 800), BUTTON_SIZE, QUIT_BUTTON_COLOR, sf::Color::White, BUTTON_TEXT_SIZE, 10);


  // Screen loop
  while ((*this->window_ptr).isOpen()) {

    // Event loop
    while ((*this->window_ptr).pollEvent((*this->event_ptr))) {
      switch ((*this->event_ptr).type) {
      case sf::Event::Closed:
        (*this->window_ptr).close();
        break;

      case sf::Event::MouseMoved:
        if (resume_button.isMouseOver(*this->window_ptr)) {
          resume_button.setBackToColor(MOUSE_OVER_COLOR);
        } else {
          resume_button.setBackToColor(PAUSE_BUTTON_COLOR);
        }

        if (quit_game_button.isMouseOver(*this->window_ptr)) {
          quit_game_button.setBackToColor(MOUSE_OVER_COLOR);
        } else {
          quit_game_button.setBackToColor(QUIT_BUTTON_COLOR);
        }
        break;

      case sf::Event::MouseButtonPressed:
        if ((resume_button.isMouseOver(*this->window_ptr))) {
          std::cout << "Resume button pressed" << std::endl;
          return true;
        }

        if ((quit_game_button.isMouseOver(*this->window_ptr))) {
          std::cout << "Quit game button pressed" << std::endl;
          
          if (this->confirmationScreen()) {
            return true;
          }
        }
        break;
      }
    }

    (*this->window_ptr).clear();

    (*this->window_ptr).draw(sprite);
    (*this->window_ptr).draw(pause_text);
    resume_button.drawButton(*this->window_ptr);
    quit_game_button.drawButton(*this->window_ptr);
    (*this->window_ptr).draw(resume_text);
    
    (*this->window_ptr).display();
  }
}