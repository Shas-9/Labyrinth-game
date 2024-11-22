#ifndef UTILITY_INCLUDE
#define UTILITY_INCLUDE

#define UTIL_CLASS Utility::getInstance()

#include <SFML/Graphics.hpp>

#include "Singleton.h"

#include "../Vector.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class Utility : public Singleton<Utility> {
private:
  sf::Clock deltaClock;
  sf::Time dt = deltaClock.restart();

public:
  Utility();
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

  void setDT();
  long getDT();
  int getTimeFactor();

  static vector<vector<sf::IntRect*>> getPlayerWalkingFrames(Vector dimensions, int scale);
  static vector<vector<sf::IntRect*>> getIronSpiderWalkingFrames(Vector dimensions, int scale);

  string player_name;
};

#endif