#include "Game.h"
#include "Utility.h"
#include "Button.h"

#define MOUSE_OVER_COLOR sf::Color (59, 5, 44)
#define PAUSE_BUTTON_COLOR sf::Color (22, 30, 43)
#define QUIT_BUTTON_COLOR sf::Color (74, 74, 46)

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

  Button pause_button("Pause Game", Vector(780, 20), Vector(200, 60), PAUSE_BUTTON_COLOR, sf::Color::White, 24, 3);

  // Loading ground textures
  sf::IntRect* rectSourceSprite = new sf::IntRect(0, 0, 60000, 60000);
  sf::Sprite* ground_sprite = new sf::Sprite();
  ground_sprite->setTexture(*util->getGroundTexture());
  ground_sprite->setTextureRect(*rectSourceSprite);
  ground_sprite->scale(sf::Vector2f(3, 3));

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
          bool resume_button_pressed = false;

          while (!(resume_button_pressed)) {
            resume_button_pressed = this->pauseScreen();
          }
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
  pause_text.setCharacterSize(100);
  pause_text.setFillColor(sf::Color::White);
  pause_text.setPosition(sf::Vector2f(160, 200));

  sf::Text resume_text;
  resume_text.setFont(font);
  resume_text.setString("All progress will be lost if you quit");
  resume_text.setCharacterSize(40);
  resume_text.setFillColor(sf::Color::White);
  resume_text.setPosition(sf::Vector2f(175, 450));

  Button resume_button("Resume", Vector(150, 600), Vector(150, 60), PAUSE_BUTTON_COLOR, sf::Color::White, 24, 4);
  Button quit_game_button("Quit Game", Vector(700, 600), Vector(150, 60), QUIT_BUTTON_COLOR, sf::Color::White, 24, 3);


  // Screen loop
  while((*this->window_ptr).isOpen()) {

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
          this->isGameOver = true;
          return true;
        }
        break;
      }
    }

    (*this->window_ptr).clear();
    (*this->window_ptr).draw(sprite);
    (*this->window_ptr).draw(pause_text);
    (*this->window_ptr).draw(resume_text);
    resume_button.drawButton(*this->window_ptr);
    quit_game_button.drawButton(*this->window_ptr);
    (*this->window_ptr).display();
  }
}