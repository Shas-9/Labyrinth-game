#include "Utility.h"

void Utility::frames_handler(
  sf::Sprite * sprite,
  int* current_frames_index,
  int* current_animation_frame,
  vector<vector<sf::IntRect*>> walking_frames,
  bool moving_left,
  bool moving_right,
  bool moving_up,
  bool moving_down,
  int speed_factor
) {
  bool is_moving = true;

  if (moving_left) {
    (*current_frames_index) = 0;
  } else if (moving_right) {
    (*current_frames_index) = 1;
  } else if (moving_up) {
    (*current_frames_index) = 2;
  } else if (moving_down) {
    (*current_frames_index) = 3;
  } else {
    is_moving = false;
  }

  if (is_moving) {
    (*current_animation_frame) = (*current_animation_frame) == (3999 / speed_factor) ? 0 : (*current_animation_frame) + 1;
    sprite->setTextureRect(*walking_frames[(*current_frames_index)][*current_animation_frame / (1000 / speed_factor)]);
  } else {
    sprite->setTextureRect(*walking_frames[(*current_frames_index)][0]);
  }
}

void Utility::loadGroundTexture() {
  this->ground_texture = new sf::Texture();
  ground_texture->loadFromFile("textures/stone_ground.png");
  ground_texture->setRepeated(true);
}

sf::Texture* Utility::getGroundTexture() {
  return this->ground_texture;
}

vector<vector<sf::IntRect*>> Utility::getIronSpiderWalkingFrames(Vector dimensions, int scale) {
  sf::IntRect* front_frame_1 = new sf::IntRect(7, 9, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* front_frame_2 = new sf::IntRect(7 + 39, 9, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* front_frame_3 = new sf::IntRect(7 + 39 * 2, 9, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* front_frame_4 = new sf::IntRect(7 + 39 * 3, 9, dimensions.getX() / scale, dimensions.getY() / scale);

  sf::IntRect* back_frame_1 = new sf::IntRect(7, 50, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* back_frame_2 = new sf::IntRect(7 + 39, 50, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* back_frame_3 = new sf::IntRect(7 + 39 * 2, 50, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* back_frame_4 = new sf::IntRect(7 + 39 * 3, 50, dimensions.getX() / scale, dimensions.getY() / scale);

  sf::IntRect* right_frame_1 = new sf::IntRect(7, 88, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* right_frame_2 = new sf::IntRect(7 + 39 * 1, 88, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* right_frame_3 = new sf::IntRect(7 + 39 * 2, 88, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* right_frame_4 = new sf::IntRect(7 + 39 * 3, 88, dimensions.getX() / scale, dimensions.getY() / scale);

  sf::IntRect* left_frame_1 = new sf::IntRect(7 , 126, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* left_frame_2 = new sf::IntRect(7 + 39 * 1, 126, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* left_frame_3 = new sf::IntRect(7 + 39 * 2, 126, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* left_frame_4 = new sf::IntRect(7 + 39 * 3, 126, dimensions.getX() / scale, dimensions.getY() / scale);

  vector<vector<sf::IntRect*>> walking_frames = {
    {
      left_frame_1,
      left_frame_2,
      left_frame_3,
      left_frame_4
    },
    {
      right_frame_1,
      right_frame_2,
      right_frame_3,
      right_frame_4
    },
    {
      back_frame_1,
      back_frame_2,
      back_frame_3,
      back_frame_4
    },
    {
      front_frame_1,
      front_frame_2,
      front_frame_3,
      front_frame_4
    }
  };

  return walking_frames;
}

vector<vector<sf::IntRect*>> Utility::getPlayerWalkingFrames(Vector dimensions, int scale) {
  sf::IntRect* front_frame_1 = new sf::IntRect(3, 2, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* front_frame_2 = new sf::IntRect(3 + 21, 2, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* front_frame_3 = new sf::IntRect(2 + 41, 2, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* front_frame_4 = new sf::IntRect(1 + 61, 2, dimensions.getX() / scale, dimensions.getY() / scale);

  sf::IntRect* back_frame_1 = new sf::IntRect(3, 21, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* back_frame_2 = new sf::IntRect(3 + 21, 21, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* back_frame_3 = new sf::IntRect(2 + 41, 21, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* back_frame_4 = new sf::IntRect(1 + 61, 21, dimensions.getX() / scale, dimensions.getY() / scale);

  sf::IntRect* left_frame_1 = new sf::IntRect(3, 41, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* left_frame_2 = new sf::IntRect(3 + 20, 41, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* left_frame_3 = new sf::IntRect(2 + 41, 41, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* left_frame_4 = new sf::IntRect(1 + 61, 41, dimensions.getX() / scale, dimensions.getY() / scale);

  sf::IntRect* right_frame_1 = new sf::IntRect(3, 60, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* right_frame_2 = new sf::IntRect(3 + 20, 60, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* right_frame_3 = new sf::IntRect(2 + 41, 60, dimensions.getX() / scale, dimensions.getY() / scale);
  sf::IntRect* right_frame_4 = new sf::IntRect(1 + 61, 60, dimensions.getX() / scale, dimensions.getY() / scale);

  vector<vector<sf::IntRect*>> walking_frames = {
    {
      left_frame_1,
      left_frame_2,
      left_frame_3,
      left_frame_4
    },
    {
      right_frame_1,
      right_frame_2,
      right_frame_3,
      right_frame_4
    },
    {
      back_frame_1,
      back_frame_2,
      back_frame_3,
      back_frame_4
    },
    {
      front_frame_1,
      front_frame_2,
      front_frame_3,
      front_frame_4
    }
  };

  return walking_frames;
}

void Utility::loadIronSpiderTexture() {
  this->iron_spider_texture = new sf::Texture();
  iron_spider_texture->loadFromFile("textures/iron_spider.png");
  iron_spider_texture->setRepeated(true);
}

sf::Texture* Utility::getIronSpiderTexture() {
  return this->iron_spider_texture;
}

void Utility::loadPlayerTexture() {
  this->player_texture = new sf::Texture();
  player_texture->loadFromFile("textures/player.png");
  player_texture->setRepeated(true);
}

sf::Texture* Utility::getPlayerTexture() {
  return this->player_texture;
}

void Utility::loadObstacleTexture() {
  this->obstacles_texture = new sf::Texture();
  obstacles_texture->loadFromFile("textures/stone_wall.png");
  obstacles_texture->setRepeated(true);
}

sf::Texture* Utility::getObstacleTexture() {
  return this->obstacles_texture;
}

void Utility::loadPotionTexture() {
  this->potion_texture = new sf::Texture();
  potion_texture->loadFromFile("textures/potion.png");
  potion_texture->setRepeated(true);
}

sf::Texture* Utility::getPotionTexture() {
  return this->potion_texture;
}

void Utility::loadCatTexture() {
  this->cat_texture = new sf::Texture();
  cat_texture->loadFromFile("textures/cat.png");
  cat_texture->setRepeated(true);
}

sf::Texture* Utility::getCatTexture() {
  return this->cat_texture;
}

void Utility::loadFastPotionTexture() {
  this->fast_texture = new sf::Texture();
  fast_texture->loadFromFile("textures/fast.jpg");
  fast_texture->setRepeated(true);
}

sf::Texture* Utility::getFastPotionTexture() {
  return this->fast_texture;
}
