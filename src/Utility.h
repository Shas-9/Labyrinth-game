#ifndef UTILITY_INCLUDE
#define UTILITY_INCLUDE

#include <SFML/Graphics.hpp>

#include "Vector.h"
#include <vector>

using std::vector;

class Utility {
private:
  sf::Texture* obstacles_texture;
  sf::Texture* ground_texture;
  sf::Texture* health_texture;
  sf::Texture* enemies_texture;
  sf::Texture* player_texture;

public:
  static void frames_handler(
    sf::Sprite * sprite,
    int* current_frames_index,
    int* current_animation_frame,
    vector<vector<sf::IntRect*>> walking_frames,
    bool moving_left,
    bool moving_right,
    bool moving_up,
    bool moving_down
  );

  void loadPlayerTexture();
  sf::Texture* getPlayerTexture();
  vector<vector<sf::IntRect*>> getPlayerWalkingFrames(Vector dimensions);

  void loadEnemyTexture();
  sf::Texture* getEnemyTexture();

  void loadObstacleTexture();
  sf::Texture* getObstacleTexture();

  void loadGroundTexture();
  sf::Texture* getGroundTexture();
};

#endif