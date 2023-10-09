#include "UI.h"
#include <iostream>

#include <SFML/Graphics.hpp>

UI::UI(Vector screen_dimensions) {
  this->screen_dimensions = screen_dimensions;

  sf::RenderWindow window(sf::VideoMode(this->screen_dimensions.getXPosition(), this->screen_dimensions.getYPosition()), "CatQuest");

  this->window_ptr = &window;
  // this->game = Game(this->window_ptr);

  Button tutorial_btn("Tutorial", Vector(600, 500), Vector(150, 100), sf::Color::Yellow, sf::Color::Black, 24);

  Button play_button("Play Game", Vector(100, 500), Vector(150, 100), sf::Color::Blue, sf::Color::Black, 24);

  while((*this->window_ptr).isOpen()) {
    sf::Event event;

    // Event loop
    while ((*this->window_ptr).pollEvent(event)) {
      switch (event.type) {

        case sf::Event::Closed:
          (*this->window_ptr).close();
          break;

        case sf::Event::MouseButtonPressed:
          if ((play_button.isMouseOver(*this->window_ptr))) {
            std::cout << "Play button pressed" << std::endl;
            // this->game.startGame(); // TODO: Fix this when Game is implemented
          } 
          else if (tutorial_btn.isMouseOver(*this->window_ptr)) {
            std::cout << "Tutorial button pressed" << std::endl;
          }
          break;
        
        case sf::Event::MouseMoved:
          if (play_button.isMouseOver(*this->window_ptr)) {
            play_button.setBackToColor(sf::Color::Red);
          } else {
            play_button.setBackToColor(sf::Color::Blue);
          }

          if (tutorial_btn.isMouseOver(*this->window_ptr)) {
            tutorial_btn.setBackToColor(sf::Color::Red);
          } else {
            tutorial_btn.setBackToColor(sf::Color::Yellow);
          }
          break;
      }
    }

    (*this->window_ptr).clear();
    this->renderUI();
    play_button.drawButton(*this->window_ptr);
    tutorial_btn.drawButton(*this->window_ptr);
    (*this->window_ptr).display();
  }
}

UI::UI(int width, int height) { UI(Vector(width, height)); }
UI::UI() { UI(Vector(600, 600)); }

void UI::renderUI() {
  sf::Texture title;
  title.loadFromFile("images/UI.png", sf::IntRect(0, 0, this->screen_dimensions.getXPosition(), this->screen_dimensions.getYPosition()));

  sf::Sprite ui_title;
  ui_title.setTexture(title);
  (*this->window_ptr).draw(ui_title);
}