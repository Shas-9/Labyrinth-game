#ifndef UTILITY_INCLUDE
#define UTILITY_INCLUDE

#define UTIL_CLASS Utility::getInstance()

#include <SFML/Graphics.hpp>

#include "Vector.h"
#include "Screen.h"
#include <vector>
#include <string>

using std::vector;

class Utility {
private:
  sf::Clock deltaClock;
  sf::Time dt = deltaClock.restart();
  Utility();

public:
  // for access inside rendering functions
  sf::RenderWindow* window_ptr;
  
  static Utility& getInstance();
  Utility(Utility const&) = delete;
  void operator=(Utility const&) = delete;

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

  Vector screen_dimensions;
  void setScreenDimensions(Vector dimensions) { this->screen_dimensions = dimensions; }
  Vector ratioVector(Vector ratio) {
    return Vector(ratio.getX() * this->screen_dimensions.getX(), ratio.getY() * this->screen_dimensions.getY()); 
  }

  void setWindowObject(sf::RenderWindow* window_ptr) { this->window_ptr = window_ptr; }
};

#endif