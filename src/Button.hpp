#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

#include "Vector.hpp"

// Button class for reusable functionality that makes shows buttons on the screen
class Button {
private:
  sf::RectangleShape button;
  sf::Text text;
  Vector position;
  Vector size;
  sf::Font arial;
  int move_text_pixels;

public:
  Button();
  Button(std::string text, Vector position, Vector size, sf::Color bgcolor,
    sf::Color textcolor, int charsize, int move_text_pixels = 0);

  void setBackToColor(sf::Color color);
  void setTextColor(sf::Color color);

  void setPosition(Vector position);
  void drawButton(sf::RenderWindow &window);
  void setString(std::string text);

  bool isMouseOver(sf::RenderWindow &window);
  void setCustomFont(std::string font_path);
};

#endif