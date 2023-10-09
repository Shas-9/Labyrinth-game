#include "Button.h"

Button::Button() {
  this->arial.loadFromFile("fonts/arial.ttf");
}

Button::Button(std::string text, Vector position, Vector size, sf::Color bgcolor, sf::Color textcolor, int charsize): Button() {
  this->text.setString(text);
  this->text.setColor(textcolor);
  this->text.setFont(this->arial);
  this->text.setCharacterSize(charsize);

  button.setSize(sf::Vector2f(size.getXPosition(), size.getYPosition()));
  button.setFillColor(bgcolor);
  
  this->setPosition(position);
}

void Button::setBackToColor(sf::Color color) {
  this->button.setFillColor(color);
}

void Button::setTextColor(sf::Color color) {
  this->text.setColor(color);
}

void Button::setPosition(Vector position) {
  this->position = position;
  this->button.setPosition(this->position.getXPosition(), this->position.getYPosition());


  // Formula for centering text in a button
  float text_x = (this->position.getXPosition() + (this->button.getSize().x / 2)) - (this->text.getLocalBounds().width / 2);
  float text_y = (this->position.getYPosition() + (this->button.getSize().y / 2)) - (this->text.getLocalBounds().height / 2);

  this->text.setPosition(text_x, text_y);
}

void Button::drawButton(sf::RenderWindow &window) {
  window.draw(this->button);
  window.draw(this->text);
}

bool Button::isMouseOver(sf::RenderWindow &window) {
  float mouse_x = sf::Mouse::getPosition(window).x;
  float mouse_y = sf::Mouse::getPosition(window).y;
  
  int button_x = this->button.getPosition().x;
  int button_y = this->button.getPosition().y;

  float button_width = this->button.getSize().x + button_x;
  float button_height = this->button.getSize().y + button_y;

  if (mouse_x < button_width && mouse_x > button_x && mouse_y < button_height && mouse_y > button_y) {
    return true;
  } else {
    return false;
  }
}


