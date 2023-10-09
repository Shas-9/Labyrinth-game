#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

#include "Vector.h"

class Button {
private:
  sf::RectangleShape button;
  sf::Text text;
  Vector position;
  Vector size;
  sf::Font arial;

public:
    Button();
    Button(std::string text, Vector position, Vector size, sf::Color bgcolor, sf::Color textcolor, int charsize);

    void setBackToColor(sf::Color color);
    void setTextColor(sf::Color color);

    void setPosition(Vector position);
    void drawButton(sf::RenderWindow &window);

    bool isMouseOver(sf::RenderWindow &window);
};

#endif