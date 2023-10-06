#include "UI.h"

#include <SFML/Graphics.hpp>

UI::UI(Vector screen_dimensions) {
  this->screen_dimensions = screen_dimensions;

  sf::RenderWindow window(sf::VideoMode(this->screen_dimensions.getXPosition(), this->screen_dimensions.getYPosition()), "CatQuest");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);
  shape.setPosition(20, 300);

  this->window_ptr = &window;
  // this->game = Game(this->window_ptr);

  while ((*this->window_ptr).isOpen()) {
    sf::Event event;
    while ((*this->window_ptr).pollEvent(event)) {
      if (event.type == sf::Event::Closed) (*this->window_ptr).close();
    }

    (*this->window_ptr).clear();
    this->renderUI();
    // this->game.renderAll();

    (*this->window_ptr).display();
  }
}

UI::UI(int width, int height) { UI(Vector(width, height)); }
UI::UI() { UI(Vector(600, 600)); }

void UI::renderUI() {
  sf::Texture title;
  title.loadFromFile("images/UI.png", sf::IntRect(0, 0, 1000, 600));

  sf::Sprite ui_title;
  ui_title.setTexture(title);
  (*this->window_ptr).draw(ui_title);
}