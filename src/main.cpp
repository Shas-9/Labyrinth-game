#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "UI.h"
#include "singleton/ScreenManager.h"
// #include "Vector.h"
// #include "Environment.h"
// #include "../testing/CamTesting.h"

#include <iostream>

struct Obj {
  Obj(Vector pos, Vector dim): pos(pos), dim(dim) {
    // this->rectangle = new sf::RectangleShape();
    this->rectangle.setFillColor(sf::Color (74, 74, 46));
    
    // Set the size of the object
    this->rectangle.setSize(sf::Vector2f(this->dim.getX(), this->dim.getY()));

    // Set the position of the object
    this->rectangle.setPosition(sf::Vector2f(this->pos.getX(), this->pos.getY()));
  }
  Vector dim;
  Vector pos;
  sf::RectangleShape rectangle;
};

class CamTesting {
public:
  CamTesting() { CamTesting(Vector(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)); }
  CamTesting(int width, int height) { CamTesting(Vector(width, height)); }

  CamTesting(Vector screen_dimensions) {
    ScreenManager::getInstance().setScreenDimensions(screen_dimensions);

    sf::RenderWindow window(sf::VideoMode(screen_dimensions.x, screen_dimensions.y), "CatQuest");
    ScreenManager::getInstance().setWindowObject(&window);

    sf::Event event;

    vector<Obj> objects = {
      Obj(Vector(10, 20), Vector(100, 200)),
      Obj(Vector(120, 50), Vector(300, 150)),
    };
    Vector camera_pos(0, 0);
    double zoom = 1;

    // Screen loop
    while (window.isOpen()) {
      // Update the current screen
      while (window.pollEvent(event)) {
        switch (event.type) {
          case sf::Event::Closed:
            window.close();
            break;

          case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::W) camera_pos.y -= 10;
            if (event.key.code == sf::Keyboard::S) camera_pos.y += 10;
            if (event.key.code == sf::Keyboard::A) camera_pos.x -= 10;
            if (event.key.code == sf::Keyboard::D) camera_pos.x += 10;

            if (event.key.code == sf::Keyboard::Z) zoom += 0.1;
            
            if (event.key.code == sf::Keyboard::X) zoom -= 0.1;
            
            break;

          case sf::Event::KeyReleased:
            // 
            break;
        }
      }

      // Render the current screen
      window.clear();
      // update
      // render
      for (Obj& obj : objects) {
        
        // update position with respect to zoom and camera
        obj.rectangle.setPosition(sf::Vector2f(obj.pos.getX()*zoom - camera_pos.getX()*1, obj.pos.getY()*zoom - camera_pos.getY()*1));
        obj.rectangle.setSize(sf::Vector2f(obj.dim.x * zoom, obj.dim.y * zoom));

        window.draw(obj.rectangle);
      }
      window.display();
    }
  }
};

int main() {
  // UI* ui = new UI();
  // UI* ui = new UI(1920/4, 1080/4);
  CamTesting* test = new CamTesting();
  return 0;
}
