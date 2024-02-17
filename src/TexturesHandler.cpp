#include "TexturesHandler.hpp"

sf::Texture* TexturesHandler::getTexture(std::string texture_location, bool repeated) {
  if (this->hash.count(texture_location) != 0) {
    hash[texture_location]->setRepeated(repeated);
    return hash[texture_location];
  } else {
    hash[texture_location] = new sf::Texture();
    hash[texture_location]->loadFromFile(texture_location);
    hash[texture_location]->setRepeated(repeated);
    return hash[texture_location];
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