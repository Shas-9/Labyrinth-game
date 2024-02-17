#ifndef UTILITY_INCLUDE
#define UTILITY_INCLUDE

#include <SFML/Graphics.hpp>

#include "Vector.h"
#include <vector>

using std::vector;

class Utility {
public:
  static void frames_handler(
    sf::Sprite * sprite,
    int* current_frames_index,
    int* current_animation_frame,
    vector<vector<sf::IntRect*>> walking_frames,
    bool moving_left,
    bool moving_right,
    bool moving_up,
    bool moving_down,
    int speed_factor
  );

  static vector<vector<sf::IntRect*>> getPlayerWalkingFrames(Vector dimensions, int scale);
  static vector<vector<sf::IntRect*>> getIronSpiderWalkingFrames(Vector dimensions, int scale);
};

#endif