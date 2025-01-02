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
}

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

  this->prev_camera_position = Vector(
    this->player.getPosition().getX() - ((ScreenManager::getInstance().screen_dimensions.getX() - this->player.getDimensions().getX()) / 2),
    this->player.getPosition().getY() - ((ScreenManager::getInstance().screen_dimensions.getY() - this->player.getDimensions().getY()) / 2)
  );
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

// Vector calcCameraPosChange(Vector current, Vector target) {
//   Vector direction = Vector::subtract(current, target);
//   direction.print();
//   direction.multiply(0.3);
//   return direction;
// }

void Game::render() {
  UTIL_CLASS.setDT();

  this->player.update();
  
  // Calculate the camera position for all rendered objects
  Vector camera_position = Vector(
    this->player.getPosition().getX() - ((ScreenManager::getInstance().screen_dimensions.getX() - this->player.getDimensions().getX()) / 2),
    this->player.getPosition().getY() - ((ScreenManager::getInstance().screen_dimensions.getY() - this->player.getDimensions().getY()) / 2)
  );

  // // Calculate the camera position for all rendered objects
  // Vector target_pos = Vector(
  //   this->player.getPosition().getX() - ((ScreenManager::getInstance().screen_dimensions.getX() - this->player.getDimensions().getX()) / 2),
  //   this->player.getPosition().getY() - ((ScreenManager::getInstance().screen_dimensions.getY() - this->player.getDimensions().getY()) / 2)
  // );
  
  // Vector change = calcCameraPosChange(this->prev_camera_position, target_pos);
  
  // // this->prev_camera_position.set(this->prev_camera_position.getX() - change.getX(), this->prev_camera_position.getY() - change.getY());
  // this->prev_camera_position.set(target_pos.getX() * 0.8, target_pos.getY() * 0.8);
  
  // Vector camera_position = this->prev_camera_position;

  // Update the ground's position relative to the player
  this->ground_sprite->setPosition(
    sf::Vector2f(
      -camera_position.getX(),
      -camera_position.getY()
    )
  );

  // Render the ground
  ScreenManager::getInstance().window_ptr->draw(*this->ground_sprite);

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