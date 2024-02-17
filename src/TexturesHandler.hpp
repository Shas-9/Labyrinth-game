#ifndef TEXTURE_HANDLER_INCLUDE
#define TEXTURE_HANDLER_INCLUDE

#define LOADTEXTURE TexturesHandler::getInstance().getTexture

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class TexturesHandler {
private:
  std::unordered_map<std::string, sf::Texture*> hash;
  TexturesHandler();
public:
  static TexturesHandler& getInstance();
  TexturesHandler(TexturesHandler const&) = delete;
  void operator=(TexturesHandler const&) = delete;

  sf::Texture* getTexture(std::string texture_location, bool repeated);
  sf::Texture* getTexture(std::string texture_location);
};

#endif