#include "Game.h"
#include "TexturesHandler.hpp"
#include "singleton/ScreenManager.h"
#include "singleton/HighscoresManager.h"

#define MOUSE_OVER_COLOR sf::Color (59, 5, 44)
#define PAUSE_BUTTON_COLOR sf::Color (22, 30, 43)
#define QUIT_BUTTON_COLOR sf::Color (74, 74, 46)
#define BUTTON_TEXT_SIZE int (40)
#define BUTTON_SIZE Vector (250, 110)

Game::Game() {
  srand(time(NULL));

  // Loading ground textures
  sf::IntRect* rectSourceSprite = new sf::IntRect(0, 0, MAP_BOUNDS / 3, MAP_BOUNDS / 3);
  sf::Sprite* ground_sprite = new sf::Sprite();
  ground_sprite->setTexture(*LOADTEXTURE("textures/stone_ground.png"));
  ground_sprite->setTextureRect(*rectSourceSprite);
  ground_sprite->scale(sf::Vector2f(3, 3));

  this->ground_sprite = ground_sprite;

  this->time_string = std::make_shared<string>("");
  this->health_string = std::make_shared<string>("");


  // // Screen loop
  // while (this->window_ptr->isOpen() && !(this->is_game_over)) {
  //   UTIL_CLASS.setDT();

  //   if (this->player.getHealth() <= 0) {
  //     this->is_game_over = true;
  //   }

  //   // Event loop
  //   while (this->window_ptr->pollEvent((*this->event_ptr))) {
  //     switch ((*this->event_ptr).type) {
  //     case sf::Event::Closed:
  //       this->window_ptr->close();
  //       break;

  //     case sf::Event::KeyPressed:
  //       if ((*this->event_ptr).key.code == sf::Keyboard::A) {
  //         this->player.setMovementDirection(0, true);
  //       }
  //       if ((*this->event_ptr).key.code == sf::Keyboard::D) {
  //         this->player.setMovementDirection(1, true);
  //       }
  //       if ((*this->event_ptr).key.code == sf::Keyboard::W) {
  //         this->player.setMovementDirection(2, true);
  //       }
  //       if ((*this->event_ptr).key.code == sf::Keyboard::S) {
  //         this->player.setMovementDirection(3, true);
  //       }
  //       break;

  //     case sf::Event::KeyReleased:
  //       if ((*this->event_ptr).key.code == sf::Keyboard::A) {
  //         this->player.setMovementDirection(0, false);
  //       }
  //       if ((*this->event_ptr).key.code == sf::Keyboard::D) {
  //         this->player.setMovementDirection(1, false);
  //       }
  //       if ((*this->event_ptr).key.code == sf::Keyboard::W) {
  //         this->player.setMovementDirection(2, false);
  //       }
  //       if ((*this->event_ptr).key.code == sf::Keyboard::S) {
  //         this->player.setMovementDirection(3, false);
  //       }
  //       if ((*this->event_ptr).key.code == sf::Keyboard::Escape) {
  //         time_elapsed = clock->getElapsedTime().asSeconds();
  //         bool resume_button_pressed = false;

  //         while (!(resume_button_pressed)) {
  //           resume_button_pressed = this->pause();
  //         }
  //         clock->restart();
  //       }
  //       break;

  //     case sf::Event::MouseMoved:
  //       if (pause_button.isMouseOver(*this->window_ptr)) {
  //         pause_button.setHoverColor();
  //       } else {
  //         pause_button.setDefaultColor();
  //       }
  //       break;

  //     case sf::Event::MouseButtonPressed:
  //       if ((pause_button.isMouseOver(*this->window_ptr))) {
  //         std::cout << "Pause button pressed" << std::endl;
  //         time_elapsed = clock->getElapsedTime().asSeconds();
  //         bool resume_button_pressed = false;

  //         while (!(resume_button_pressed)) {
  //           resume_button_pressed = this->pause();
  //         }
  //         clock->restart();
  //       }

  //       break;
  //     }
  //   }

  //   this->window_ptr->clear();

  //   // // Player movement
  //   // if (this->player.getMovementDirection(0)) {
  //   //   this->player.moveLeft();
  //   // }
  //   // if (this->player.getMovementDirection(1)) {
  //   //   this->player.moveRight();
  //   // }
  //   // if (this->player.getMovementDirection(2)) {
  //   //   this->player.moveUp();
  //   // }
  //   // if (this->player.getMovementDirection(3)) {
  //   //   this->player.moveDown();
  //   // }

    

  //   this->window_ptr->display();
  // }
}

// bool Game::confirmationScreen() {
//   sf::Texture texture;
//   texture.loadFromFile("images/UI.png");
//   sf::Sprite sprite;
//   sprite.setTexture(texture);
//   sprite.setTextureRect(sf::IntRect(0, 0, this->window_ptr->getSize().x, this->window_ptr->getSize().y));

//   sf::Font font;
//   font.loadFromFile("fonts/MouldyCheese.ttf");
//   sf::Text quit_text;
//   quit_text.setFont(font);
//   quit_text.setString("Are you sure you want to quit?");
//   quit_text.setCharacterSize(46);
//   quit_text.setFillColor(sf::Color::White);
//   quit_text.setPosition(sf::Vector2f(580, 650));

//   Button yes_button("Yes", Vector(300, 800), BUTTON_SIZE, sf::Color::White, PAUSE_BUTTON_COLOR, sf::Color::White, PAUSE_BUTTON_COLOR, BUTTON_TEXT_SIZE, 10);
//   Button no_button("No", Vector(1300, 800), BUTTON_SIZE, sf::Color::White, QUIT_BUTTON_COLOR, sf::Color::White, QUIT_BUTTON_COLOR, BUTTON_TEXT_SIZE, 10);

//   // Screen loop
//   while (this->window_ptr->isOpen()) {

//     // Event loop
//     while (this->window_ptr->pollEvent((*this->event_ptr))) {
//       switch ((*this->event_ptr).type) {
//       case sf::Event::Closed:
//         this->window_ptr->close();
//         break;

//       case sf::Event::MouseMoved:
//         if (yes_button.isMouseOver(*this->window_ptr)) {
//           yes_button.setHoverColor();
//         } else {
//           yes_button.setDefaultColor();
//         }

//         if (no_button.isMouseOver(*this->window_ptr)) {
//           no_button.setHoverColor();
//         } else {
//           no_button.setDefaultColor();
//         }
//         break;

//       case sf::Event::MouseButtonPressed:
//         if ((yes_button.isMouseOver(*this->window_ptr))) {
//           std::cout << "Yes button pressed" << std::endl;
//           this->is_game_over = true;
//           return true;
//         }

//         if ((no_button.isMouseOver(*this->window_ptr))) {
//           std::cout << "No button pressed" << std::endl;
//           return false;
//         }
//       }
//     }

//     this->window_ptr->clear();

//     this->window_ptr->draw(sprite);
//     yes_button.drawButton(*this->window_ptr);
//     no_button.drawButton(*this->window_ptr);
//     this->window_ptr->draw(quit_text);

//     this->window_ptr->display();

//   }

//   return true;
// }

// bool Game::pause() {
//   sf::Texture texture;
//   texture.loadFromFile("images/UI.png");
//   sf::Sprite sprite;
//   sprite.setTexture(texture);
//   sprite.setTextureRect(sf::IntRect(0, 0, this->window_ptr->getSize().x, this->window_ptr->getSize().y));

//   sf::Font font;
//   font.loadFromFile("fonts/MouldyCheese.ttf");
//   sf::Font cat_font;
//   cat_font.loadFromFile("fonts/cat_font.ttf");

//   sf::Text pause_text;
//   pause_text.setFont(cat_font);
//   pause_text.setString("Game Paused");
//   pause_text.setCharacterSize(130);
//   pause_text.setFillColor(sf::Color::White);
//   pause_text.setPosition(sf::Vector2f(500, 350));

//   sf::Text resume_text;
//   resume_text.setFont(font);
//   resume_text.setString("All progress will be lost if you quit");
//   resume_text.setCharacterSize(46);
//   resume_text.setFillColor(sf::Color::White);
//   resume_text.setPosition(sf::Vector2f(580, 650));

//   Button resume_button("Resume", Vector(300, 800), BUTTON_SIZE, sf::Color::White, PAUSE_BUTTON_COLOR, sf::Color::White, PAUSE_BUTTON_COLOR, BUTTON_TEXT_SIZE, 10);
//   Button quit_game_button("Quit Game", Vector(1300, 800), BUTTON_SIZE, sf::Color::White, QUIT_BUTTON_COLOR, sf::Color::White, QUIT_BUTTON_COLOR, BUTTON_TEXT_SIZE, 10);


//   // Screen loop
//   while (this->window_ptr->isOpen()) {

//     // Event loop
//     while (this->window_ptr->pollEvent((*this->event_ptr))) {
//       switch ((*this->event_ptr).type) {
//       case sf::Event::Closed:
//         this->window_ptr->close();
//         break;

//       case sf::Event::MouseMoved:
//         if (resume_button.isMouseOver(*this->window_ptr)) {
//           resume_button.setHoverColor();
//         } else {
//           resume_button.setDefaultColor();
//         }

//         if (quit_game_button.isMouseOver(*this->window_ptr)) {
//           quit_game_button.setHoverColor();
//         } else {
//           quit_game_button.setDefaultColor();
//         }
//         break;

//       case sf::Event::MouseButtonPressed:
//         if ((resume_button.isMouseOver(*this->window_ptr))) {
//           std::cout << "Resume button pressed" << std::endl;
//           return true;
//         }

//         if ((quit_game_button.isMouseOver(*this->window_ptr))) {
//           std::cout << "Quit game button pressed" << std::endl;

//           if (this->confirmationScreen()) {
//             return true;
//           }
//         }
//         break;
//       }
//     }

//     this->window_ptr->clear();

//     this->window_ptr->draw(sprite);
//     this->window_ptr->draw(pause_text);
//     resume_button.drawButton(*this->window_ptr);
//     quit_game_button.drawButton(*this->window_ptr);
//     this->window_ptr->draw(resume_text);

//     this->window_ptr->display();
//   }

//   return true;
// }

void Game::setGamePaused(bool isPaused) {
  this->is_game_paused = isPaused;
  
  if (isPaused) {
    this->time_offset += this->clock.getElapsedTime().asMilliseconds();
  } else {
    // For remaining time
    this->clock.restart();
    // For animation and game speed
    UTIL_CLASS.setDT();
    // Stop the player from moving (should this be done for other entities as well? not really)
    this->player.setMovementDirection(0, false);
    this->player.setMovementDirection(1, false);
    this->player.setMovementDirection(2, false);
    this->player.setMovementDirection(3, false);
  }
}


void Game::startGame() {
  this->environment = std::make_shared<Environment>();
  this->is_game_won = false;
  this->is_game_paused = false;
  this->is_game_over = false;

  // Create the player object
  this->player = Player(
    Vector(MAZE_BOX_THICKNESS + 10, MAZE_BOX_THICKNESS + 10),
    Vector(140 / 2, 180 / 2),
    "player",
    3,
    10000,
    10,
    this->environment
  );

  this->time_offset = 0;
  this->clock.restart();
}

void Game::update() {
  string time_left = std::to_string(std::ceil(((double)((long int)(this->clock.getElapsedTime().asMilliseconds()) + this->time_offset)/1000) * 100.0) / 100.0);
  time_left.erase ( time_left.find_last_not_of('0') + 1, std::string::npos );
  time_left.erase ( time_left.find_last_not_of('.') + 1, std::string::npos );
  *this->time_string = "Time: " + time_left + "s";

  string health_left = std::to_string(this->player.getHealth());
  *this->health_string = "Health: " + health_left;

  if (this->player.getHealth() <= 0) {
    this->loseGame();
  }
}

void Game::render() {
  UTIL_CLASS.setDT();

  this->player.update();
  
  // Calculate the camera position for all rendered objects
  Vector camera_position = Vector(
    this->player.getPosition().getX() - ((ScreenManager::getInstance().screen_dimensions.getX() - this->player.getDimensions().getX()) / 2),
    this->player.getPosition().getY() - ((ScreenManager::getInstance().screen_dimensions.getY() - this->player.getDimensions().getY()) / 2)
  );

  // Update the ground's position relative to the player
  ground_sprite->setPosition(
    sf::Vector2f(
      -camera_position.getX(),
      -camera_position.getY()
    )
  );

  // Render the ground
  ScreenManager::getInstance().window_ptr->draw(*ground_sprite);

  // Render obstacles' walls (for 3D illusion)
  for (int i = 0; i < this->environment->getObstaclesNum(); i++) {
    this->environment->getObstacles()[i].render_right_wall(ScreenManager::getInstance().window_ptr, camera_position);
  }
  // Render obstacles' walls (for 3D illusion)
  for (int i = 0; i < this->environment->getObstaclesNum(); i++) {
    this->environment->getObstacles()[i].render_bottom_wall(ScreenManager::getInstance().window_ptr, camera_position);
  }

  // Render all obstacles/walls of the cave
  for (int i = 0; i < this->environment->getObstaclesNum(); i++) {
    this->environment->getObstacles()[i].render(ScreenManager::getInstance().window_ptr, camera_position);
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
      this->player.loseHealth(this->environment->getEnemies()[i].getAttackDamage() * UTIL_CLASS.getTimeFactor());
    }

    this->environment->getEnemies()[i].render(ScreenManager::getInstance().window_ptr, camera_position);
    this->environment->getEnemies()[i].update();
  }

  // Render and update all items
  for (int i = 0; i < this->environment->getItemsNum(); i++) {
    Item* current_item = &(this->environment->getItems()[i]);
    current_item->render(ScreenManager::getInstance().window_ptr, camera_position);

    if (current_item->isCollidingWithObject(&this->player)) {
      // Use item
      if (current_item->getType() == "health") {
        this->player.gainHealth(400);
        this->environment->removeItem(i);
      }
    }
  }

  Cat cat_item = this->environment->getCat();
  Item* cat_ptr = &cat_item;
  cat_ptr->render(ScreenManager::getInstance().window_ptr, camera_position);
  if (cat_ptr->isCollidingWithObject(&this->player)) {
    if (cat_ptr->getValue() == 123) {
      this->winGame();
    }
  }

  // Render the player
  this->player.render(ScreenManager::getInstance().window_ptr, ScreenManager::getInstance().screen_dimensions);
}

void Game::winGame() {
  this->is_game_won = true;
  this->is_game_over = true;
  long int final_score = this->time_offset + this->clock.getElapsedTime().asMilliseconds();
  
  bool is_highscore = HighscoresManager::getInstance().isHighscore(final_score);
  HighscoresManager::getInstance().addScore(UTIL_CLASS.player_name, final_score);
  
  if (is_highscore) ScreenManager::getInstance().switchScreen("highscore_winning_screen");
  else ScreenManager::getInstance().switchScreen("winning_screen");
  
}

void Game::loseGame() {
  this->is_game_over = true;
  this->is_game_won = false;
  ScreenManager::getInstance().switchScreen("losing_screen");
}