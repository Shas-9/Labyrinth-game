#include "Button.h"

// Default constructor that loads the font for the test in the button
Button::Button() {
  this->arial.loadFromFile("fonts/arial.ttf");
}

// Overloaded constructor for setting the size, color, and other propoerties of the button
Button::Button(
  std::string text,
  Vector position,
  Vector size,
  sf::Color bgcolor,
  sf::Color textcolor,
  int charsize,
  int move_text_pixels
) : Button() {
  this->text.setString(text);
  this->text.setColor(textcolor);
  this->text.setFont(this->arial);
  this->text.setCharacterSize(charsize);

  this->move_text_pixels = move_text_pixels;

  button.setSize(sf::Vector2f(size.getX(), size.getY()));
  button.setFillColor(bgcolor);

  this->setPosition(position);
}

// Changing the color of the button
void Button::setBackToColor(sf::Color color) {
  this->button.setFillColor(color);
}

// Set the color fo the text for the button
void Button::setTextColor(sf::Color color) {
  this->text.setColor(color);
}

// Setting the position of the button and text
void Button::setPosition(Vector position) {
  this->position = position;
  this->button.setPosition(this->position.getX(), this->position.getY());

  // Formula for centering text in the horizontal and vertical centers of the button
  float text_x = (this->position.getX() - 4 + (this->button.getSize().x / 2)) - (this->text.getLocalBounds().width / 2);
  float text_y = (this->position.getY() - this->move_text_pixels + (this->button.getSize().y / 2)) - (this->text.getLocalBounds().height / 2);

  this->text.setPosition(text_x, text_y);
}

// Displying the button on the screen
void Button::drawButton(sf::RenderWindow &window) {
  window.draw(this->button);
  window.draw(this->text);
}

// Checking if the mouse is hovering over the button
bool Button::isMouseOver(sf::RenderWindow &window) {
  // Getting current mouse position
  float mouse_x = sf::Mouse::getPosition(window).x;
  float mouse_y = sf::Mouse::getPosition(window).y;

  // Button position
  int button_x = this->button.getPosition().x;
  int button_y = this->button.getPosition().y;

  // Button dimensions
  float button_width = this->button.getSize().x + button_x;
  float button_height = this->button.getSize().y + button_y;

  // Check if the mouse location lies within the dimensinos of the button
  if (mouse_x < button_width && mouse_x > button_x && mouse_y < button_height && mouse_y > button_y) {
    return true;
  } else {
    return false;
  }
}

// Setting the text of the button
void Button::setString(std::string text) {
  this->text.setString(text);
  this->setPosition(this->position);
}

// Setting a custom font
void Button::setCustomFont(std::string font_path) {
  this->arial.loadFromFile(font_path);
  this->text.setFont(this->arial);
  this->setPosition(this->position);
}