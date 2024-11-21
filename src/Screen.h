#ifndef SCREEN_INCLUDE
#define SCREEN_INCLUDE

#include "global.h"
#include "Button.h"
#include <vector>
#include <memory>

using std::vector;
using std::pair;
using std::string;

struct ScreenButton {
  ScreenButton(Button* button, void (*func)()): button(button), func(func) {}
  Button* button;
  void (*func)();
};

struct ScreenImage {
  ScreenImage(string location, Vector position, Vector dimensions, Vector scale) {
    this->texture = std::make_shared<sf::Texture>();
    this->sprite = std::make_shared<sf::Sprite>();

    texture->loadFromFile(location, sf::IntRect(
      position.getX(), position.getY(), position.getX() + dimensions.getX(), position.getY() + dimensions.getY()
    ));

    sprite->setScale(scale.getX(), scale.getY());
    sprite->setTexture(*texture);
  }
  
  std::shared_ptr<sf::Texture> texture;
  std::shared_ptr<sf::Sprite> sprite;
};

struct ScreenText {
  ScreenText(string text, Vector text_position, int text_size, string font_location, double screen_width) {
    this->text = std::make_shared<sf::Text>();
    this->text_font = std::make_shared<sf::Font>();

    this->text_font->loadFromFile(font_location);
    this->text->setFont(*text_font);
    this->text->setString(text);
    this->text->setCharacterSize(screen_width*text_size/100);
    this->text->setFillColor(sf::Color::White);
    
    this->text->setPosition(text_position.getX(), text_position.getY());
  }

  std::shared_ptr<sf::Text> text;
  std::shared_ptr<sf::Font> text_font;
  
};

class Screen {
private:
  vector<ScreenButton> buttons;
  vector<ScreenText> texts;
  vector<ScreenImage> images;
public:
  string screen_name;

  Screen(string screen_name, vector<ScreenButton> buttons, vector<ScreenText> texts, vector<ScreenImage> images);
  void render();
  void update(sf::Event event);
};

#endif