#include "TexturesHandler.hpp"

sf::Texture* TexturesHandler::getTexture(std::string texture_location, bool repeated) {
  if (this->textures.count(texture_location) != 0) {
    textures[texture_location]->setRepeated(repeated);
    return textures[texture_location];
  } else {
    textures[texture_location] = new sf::Texture();
    textures[texture_location]->loadFromFile(texture_location);
    textures[texture_location]->setRepeated(repeated);
    return textures[texture_location];
  }
}

sf::Texture* TexturesHandler::getTexture(std::string texture_location) {
  return this->getTexture(texture_location, true);
}

TexturesHandler& TexturesHandler::getInstance() {
  static TexturesHandler instance;
  return instance;
}

TexturesHandler::TexturesHandler() {}