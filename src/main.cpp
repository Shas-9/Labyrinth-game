#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "UI.h"
#include "singleton/ScreenManager.h"

#include "StaticQuadTree.tpp"
#include <ctime>
#include <cmath>
#include <iostream>

#define SCREEN_X ScreenManager::getInstance().screen_dimensions.x
#define SCREEN_Y ScreenManager::getInstance().screen_dimensions.y

struct Obj {
  Obj(Vector pos, Vector dim) : pos(pos), dim(dim) {
    // this->rectangle = new sf::RectangleShape();
    this->rectangle.setFillColor(sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256));

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

void constructQuadTree(StaticQuadTreeContainer<Obj>& qt, vector<AreaRect>& rects, vector<Obj>& objs) {
  qt.resize(AreaRect(0, 0, 10000, 10000));
  for (int i = 0; i < rects.size(); i++) qt.insert(objs[i], rects[i]);
}

void generateBoxes(vector<AreaRect>& boxes, AreaRect bounds, int num_boxes) {
  for (int i = 0; i < num_boxes; i++) {
    int box_width = 50 + (std::rand() % 50+1);
    int box_height = 50 + (std::rand() % 50+1);
    int box_x = bounds.pos.x + std::rand() % (int)(bounds.size.x + 1 - box_width);
    int box_y = bounds.pos.y + std::rand() % (int)(bounds.size.y + 1 - box_height);
    boxes.push_back(AreaRect(box_x, box_y, box_width, box_height));
  }
}

class CamTesting {
public:
  CamTesting() { CamTesting(Vector(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)); }
  CamTesting(int width, int height) { CamTesting(Vector(width, height)); }

  CamTesting(Vector screen_dimensions) {
    ScreenManager::getInstance().setScreenDimensions(screen_dimensions);

    sf::RenderWindow window(sf::VideoMode(screen_dimensions.x, screen_dimensions.y), "CatQuest");
    ScreenManager::getInstance().setWindowObject(&window);

    vector<AreaRect> rects;
    generateBoxes(rects, AreaRect(0, 0, 15000, 15000), 150000);

    vector<Obj> objects = {};
    for (const auto& rect : rects) { objects.push_back(Obj(rect.pos, rect.size)); }

    StaticQuadTreeContainer<Obj> qt_container;
    constructQuadTree(qt_container, rects, objects);

    Vector target_camera_pos(0, 0);
    double zoom = 1 * SCREEN_Y/1080;

    Vector current_camera_pos(0, 0);

    sf::Font font;
    font.loadFromFile("fonts/arial.ttf");

    sf::Text coords;
    coords.setFont(font);
    coords.setCharacterSize(24);
    coords.setPosition(10, 10);

    sf::Text objs_count;
    objs_count.setFont(font);
    objs_count.setCharacterSize(24);
    objs_count.setPosition(10, 45);

    bool mouse_pressed;
    double old_mouse_x = 10000;
    double old_mouse_y = 10000;

    sf::Event event;
    
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

        case sf::Event::MouseWheelScrolled:
          zoom *= pow(1.4, event.mouseWheelScroll.delta);
          break;
        
        case sf::Event::MouseButtonPressed:
          if (event.mouseButton.button == sf::Mouse::Left) mouse_pressed = true;
          break;
        case sf::Event::MouseButtonReleased:
          if (event.mouseButton.button == sf::Mouse::Left) mouse_pressed = false;
          old_mouse_x = 10000;
          old_mouse_y = 10000;
          break;

        case sf::Event::MouseMoved: 
          if (mouse_pressed) {
            if (old_mouse_x == 10000 && old_mouse_y == 10000) {
              old_mouse_x = event.mouseMove.x;
              old_mouse_y = event.mouseMove.y;
            }

            double delta_x = old_mouse_x - event.mouseMove.x;
            double delta_y = old_mouse_y - event.mouseMove.y;

            target_camera_pos.x += delta_x/zoom;
            target_camera_pos.y += delta_y/zoom;

            old_mouse_x = event.mouseMove.x;
            old_mouse_y = event.mouseMove.y;
          }
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
      Vector new_cam_pos = Vector::getMid(current_camera_pos, target_camera_pos, 10);
      current_camera_pos = new_cam_pos;

      // // instant caera movement
      // current_camera_pos = target_camera_pos;

      Vector screen_size = Vector(SCREEN_X/zoom/1.01, SCREEN_Y/zoom/1.01);
      Vector screen_pos(current_camera_pos.getX() - screen_size.x/2, current_camera_pos.getY() - screen_size.y/2);
      auto objects_in_camera = qt_container.search(AreaRect(screen_pos, screen_size));

      // render
      for (const auto& obj_ptr : objects_in_camera) {
        // update position with respect to zoom and camera
        obj_ptr->rectangle.setPosition(sf::Vector2f(obj_ptr->pos.getX() * zoom - current_camera_pos.getX() * zoom + SCREEN_X/2, obj_ptr->pos.getY() * zoom - current_camera_pos.getY() * zoom + SCREEN_Y/2));
        obj_ptr->rectangle.setSize(sf::Vector2f(obj_ptr->dim.x * zoom, obj_ptr->dim.y * zoom));
        
        window.draw(obj_ptr->rectangle);
      }

      string cam_pos = "Camera {" + std::to_string(current_camera_pos.x) + ", " + std::to_string(current_camera_pos.y) + "}";
      coords.setString(cam_pos);
      window.draw(coords);

      string objs_count_str = std::to_string(objects_in_camera.size()) + " objects on screen";
      objs_count.setString(objs_count_str);
      window.draw(objs_count);

      window.display();
    }
  }
};

int main() {
  srand(time(0));
  // UI* ui = new UI();
  // UI* ui = new UI(800, 500);
  // UI* ui = new UI(1920/4, 1080/4);
  CamTesting *test = new CamTesting();
  // CamTesting *test = new CamTesting(1920/1.7, 1080/1.7);
  

  return 0;
}
