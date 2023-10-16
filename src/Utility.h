#ifndef UTILITY_INCLUDE
#define UTILITY_INCLUDE

#include <SFML/Graphics.hpp>

class Utility {
private:
  sf::Texture* texture;

public:
  void setObstacleTexture();
  sf::Texture* getObstacleTexture();
};

#endif