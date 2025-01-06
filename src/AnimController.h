#ifndef ANIM_CONTROLLER_INCLUDE
#define ANIM_CONTROLLER_INCLUDE

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Vector.h"
#include "Camera.h"

class AnimController {
protected:
  // name of activity/interaction
  std::unordered_map<std::string, int> activities_map;

  // dimension of frames for each row
  std::vector<Vector> frames_dimensions;

  // how many frames in each row
  std::vector<int> frames_numbers;

  sf::IntRect texture_rect;
  std::shared_ptr<sf::Sprite> sprite;

  int current_row;
  int current_frame_progress;

  bool temp_reset;

public:
  AnimController();
  void addRow(Vector frames_dimension, int frames_number, std::string activity_name);
  sf::IntRect getTextureRect();

  void setActivity(std::string activity);
  void resetFrames();
  void updateFrame(int animation_speed, std::string mode);

  void tempResetFrames();
  void tempResumeFrames();
};

#endif