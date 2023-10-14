#include "UI.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

UI::UI(Vector screen_dimensions) {
  this->screen_dimensions = screen_dimensions;

  sf::RenderWindow window(sf::VideoMode(this->screen_dimensions.getXPosition(),
                                        this->screen_dimensions.getYPosition()),
                          "CatQuest");

  this->window_ptr = &window;
  // this->game = Game(this->window_ptr);

  Button tutorial_btn("Tutorial", Vector(600, 500), Vector(150, 100),
                      sf::Color::Yellow, sf::Color::Black, 24);

  Button play_button("Play Game", Vector(100, 500), Vector(150, 100),
                     sf::Color::Blue, sf::Color::Black, 24);

  sf::Event event;
  this->event_ptr = &event;

  while ((*this->window_ptr).isOpen()) {
    std::cout << "LOOP 1 RUNNING" << std::endl;

    // Event loop
    while ((*this->window_ptr).pollEvent((*this->event_ptr))) {
      switch (event.type) {
        case sf::Event::Closed:
          (*this->window_ptr).close();
          break;

        case sf::Event::MouseButtonPressed:
          if ((play_button.isMouseOver(*this->window_ptr))) {
            std::cout << "Play button pressed" << std::endl;
            // this->game.startGame(); // TODO: Fix this when Game is
            // implemented
          } else if (tutorial_btn.isMouseOver(*this->window_ptr)) {
            std::cout << "Tutorial button pressed" << std::endl;
            bool menu_button_pressed = false;

            while (!(menu_button_pressed)) {
              menu_button_pressed = this->drawTutorial();
            }
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
  title.loadFromFile("images/UI.png",
                     sf::IntRect(0, 0, this->screen_dimensions.getXPosition(),
                                 this->screen_dimensions.getYPosition()));

  sf::Sprite ui_title;
  ui_title.setTexture(title);
  (*this->window_ptr).draw(ui_title);
}

void UI::fetchHighScores() {
  std::ifstream names_file("highscores/names.txt");
  std::ifstream scores_file("highscores/scores.txt");

  std::string name;
  std::string score;

  while (getline(names_file, name)) {
    getline(scores_file, score);

    this->highscores.insert({name, std::stoi(score)});
  }
  names_file.close();
  scores_file.close();
}

bool UI::drawTutorial() {
  sf::Text how_to_play;
  sf::Font arial;
  arial.loadFromFile("fonts/arial.ttf");
  how_to_play.setFont(arial);
  how_to_play.setString("Game control instructions");
  how_to_play.setCharacterSize(24);
  how_to_play.setFillColor(sf::Color::White);
  how_to_play.setPosition(100, 100);

  Button menu("Back to Menu", Vector(100, 500), Vector(200, 150),
              sf::Color::Blue, sf::Color::Black, 24);

  while ((*this->window_ptr).isOpen()) {
    while ((*this->window_ptr).pollEvent((*this->event_ptr))) {
      switch ((*this->event_ptr).type) {
        case sf::Event::Closed:
          (*this->window_ptr).close();
          break;

        case sf::Event::MouseButtonPressed:
          if ((menu.isMouseOver(*this->window_ptr))) {
            std::cout << "Menu button pressed" << std::endl;
            // menu_button_pressed = true;
            return true;
          }
          break;

        case sf::Event::MouseMoved:
          if (menu.isMouseOver(*this->window_ptr)) {
            menu.setBackToColor(sf::Color::Red);
          } else {
            menu.setBackToColor(sf::Color::Blue);
          }
          break;
      }
    }

    (*this->window_ptr).clear();
    (*this->window_ptr).draw(how_to_play);
    menu.drawButton(*this->window_ptr);
    (*this->window_ptr).display();
  }
}
