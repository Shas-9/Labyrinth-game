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
    *current_animation_frame += speed_factor*UTIL_CLASS.getTimeFactor();
    if (*current_animation_frame >= 4000) *current_animation_frame = 0;

    sprite->setTextureRect(*walking_frames[(*current_frames_index)][*current_animation_frame / 1000]);
  } else {
    sprite->setTextureRect(*walking_frames[(*current_frames_index)][0]);
  }
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

  sf::IntRect* left_frame_1 = new sf::IntRect(7, 126, dimensions.getX() / scale, dimensions.getY() / scale);
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

Utility& Utility::getInstance() {
  static Utility instance;
  return instance;
}

Utility::Utility() {}

void Utility::setDT() {
  this->dt = this->deltaClock.restart();
}

long Utility::getDT() {
  return this->dt.asMicroseconds();
}

int Utility::getTimeFactor() {
  long delta_time = this->getDT();

  int time_factor;
  // if delta time is less than five seconds
  if (delta_time < 5000000) time_factor = (int)(delta_time / 1000 / 2);
  else time_factor = 0;

  return time_factor;
}

void Utility::setRenderWindow(sf::RenderWindow* window) { this->window = window; }
sf::RenderWindow* Utility::getRenderWindow() { return this->window; }