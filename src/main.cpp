#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "UI.h"
#include "singleton/ScreenManager.h"
// #include "Vector.h"
// #include "Environment.h"
// #include "../testing/CamTesting.h"

#include <iostream>

#define SCREEN_X ScreenManager::getInstance().screen_dimensions.x
#define SCREEN_Y ScreenManager::getInstance().screen_dimensions.y

struct Obj {
  Obj(Vector pos, Vector dim) : pos(pos), dim(dim) {
    // this->rectangle = new sf::RectangleShape();
    this->rectangle.setFillColor(sf::Color(74, 74, 46));

    // Set the size of the object
    this->rectangle.setSize(sf::Vector2f(this->dim.getX(), this->dim.getY()));

    // Set the position of the object
    this->rectangle.setPosition(
        sf::Vector2f(this->pos.getX(), this->pos.getY()));
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
        Obj(Vector(1200, 50), Vector(300, 150)),
    };
    Vector target_camera_pos(0, 0);
    double zoom = 1 * SCREEN_Y/1080;

    Vector current_camera_pos(0, 0);

    sf::Font font;
    font.loadFromFile("fonts/arial.ttf");

    sf::Text coords;
    coords.setFont(font);
    coords.setCharacterSize(24);
    coords.setPosition(10, 10);

    // Screen loop
    while (window.isOpen()) {
      // Update the current screen
      while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;

        case sf::Event::KeyPressed:
          if (event.key.code == sf::Keyboard::W)
            target_camera_pos.y -= 30;
          if (event.key.code == sf::Keyboard::S)
            target_camera_pos.y += 30;
          if (event.key.code == sf::Keyboard::A)
            target_camera_pos.x -= 30;
          if (event.key.code == sf::Keyboard::D)
            target_camera_pos.x += 30;

          if (event.key.code == sf::Keyboard::Z)
            zoom += 0.1;

          if (event.key.code == sf::Keyboard::X)
            zoom -= 0.1;

          break;

        case sf::Event::KeyReleased:
          //
          break;
        }
      }

      // Render the current screen
      window.clear();
      // update

      // smooth camera movement
      Vector new_cam_pos = Vector::getMid(current_camera_pos, target_camera_pos, 50);
      current_camera_pos = new_cam_pos;

      // // instant caera movement
      // current_camera_pos = target_camera_pos;

      // render
      for (Obj &obj : objects) {

        // update position with respect to zoom and camera
        obj.rectangle.setPosition(sf::Vector2f(obj.pos.getX() * zoom - current_camera_pos.getX() * zoom + SCREEN_X/2, obj.pos.getY() * zoom - current_camera_pos.getY() * zoom + SCREEN_Y/2));
        obj.rectangle.setSize(sf::Vector2f(obj.dim.x * zoom, obj.dim.y * zoom));
        
        window.draw(obj.rectangle);

        string cam_pos = "Camera {" + std::to_string(current_camera_pos.x) + ", " + std::to_string(current_camera_pos.y) + "}";
        coords.setString(cam_pos);
        window.draw(coords);
      }
      window.display();
    }
  }
};

int main() {
  UI* ui = new UI();
  // UI* ui = new UI(1920/4, 1080/4);
  // CamTesting *test = new CamTesting();
  // CamTesting *test = new CamTesting(1920/4, 1080/4);

  return 0;
}
