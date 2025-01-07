#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <chrono>
using namespace std::chrono_literals;

// #include "UI.h"
#include "singleton/ScreenManager.h"

#include "QuadTree.tpp"
#include <ctime>
#include <cmath>
#include <iostream>

#define SCREEN_X ScreenManager::getInstance().screen_dimensions.x
#define SCREEN_Y ScreenManager::getInstance().screen_dimensions.y

struct Obj {
  Obj(Vector pos, Vector dim, const sf::Color color = sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256)) : pos(pos), dim(dim) {
    // this->rectangle = new sf::RectangleShape();
    this->rectangle.setFillColor(color);

    // Set the size of the object
    this->rectangle.setSize(sf::Vector2f(this->dim.x, this->dim.y));

    // Set the position of the object
    this->rectangle.setPosition(
        sf::Vector2f(this->pos.x, this->pos.y));
  }
  void render(Vector current_camera_pos, double zoom) {
    // update position with respect to zoom and camera
    this->rectangle.setPosition(sf::Vector2f(this->pos.x * zoom - current_camera_pos.x * zoom + SCREEN_X/2, this->pos.y * zoom - current_camera_pos.y * zoom + SCREEN_Y/2));
    this->rectangle.setSize(sf::Vector2f(this->dim.x * zoom, this->dim.y * zoom));
    
    (*ScreenManager::getInstance().window_ptr).draw(this->rectangle);
  }
  void render() {
    this->rectangle.setPosition(sf::Vector2f(this->pos.x, this->pos.y));
    this->rectangle.setSize(sf::Vector2f(this->dim.x, this->dim.y));
    
    (*ScreenManager::getInstance().window_ptr).draw(this->rectangle);
  }
  Vector dim;
  Vector pos;
  sf::RectangleShape rectangle;
};

void constructQuadTree(StaticQuadTreeContainer<Obj>& qt_container, AreaRect& qt_area, vector<AreaRect>& rects, vector<Obj>& objs) {
  qt_container.resize(qt_area);
  for (int i = 0; i < rects.size(); i++) qt_container.insert(objs[i], rects[i]);
  std::cout << qt_container.size() << std::endl;
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

    AreaRect map_boundary(0, 0, 150000, 150000);
    Obj map_boundary_obj(map_boundary.pos, map_boundary.size);

    vector<AreaRect> rects;
    generateBoxes(rects, map_boundary, 100000);

    vector<Obj> objects = {};
    for (const auto& rect : rects) { objects.push_back(Obj(rect.pos, rect.size)); }

    StaticQuadTreeContainer<Obj> qt_container;
    constructQuadTree(qt_container, map_boundary, rects, objects);
    
    // qt_container.visualizeTree("testing/static-quad-tree.dot"); 

    Vector target_camera_pos(0, 0);
    double zoom = 1 * SCREEN_Y/1080;

    Vector current_camera_pos(0, 0);

    sf::Font font;
    font.loadFromFile("fonts/MouldyCheese.ttf");

    sf::Text coords;
    coords.setFont(font);
    coords.setCharacterSize(24);
    coords.setPosition(10, 10);

    bool mouse_pressed;
    double old_mouse_x = 10000;
    double old_mouse_y = 10000;

    bool quadTreeMode = true;

    Obj text_bg(Vector(0, 0), Vector(460, 130), sf::Color(1, 1, 1, 150));

    sf::Event event;

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::seconds;

    // Screen loop
    while (window.isOpen()) {
      auto t1 = high_resolution_clock::now();

      // Update the current screen
      while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;

        case sf::Event::KeyPressed:
          if (event.key.code == sf::Keyboard::W) target_camera_pos.y -= 3000;
          if (event.key.code == sf::Keyboard::S) target_camera_pos.y += 3000;
          if (event.key.code == sf::Keyboard::A) target_camera_pos.x -= 3000;
          if (event.key.code == sf::Keyboard::D) target_camera_pos.x += 3000;

          if (event.key.code == sf::Keyboard::Z) zoom += 0.1;
          if (event.key.code == sf::Keyboard::X) zoom -= 0.1;

          if (event.key.code == sf::Keyboard::Tab) quadTreeMode = !quadTreeMode;
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

      // map_boundary_obj.render(current_camera_pos, zoom);

      Vector screen_size(SCREEN_X/zoom, SCREEN_Y/zoom);
      Vector screen_pos(current_camera_pos.x - screen_size.x/2, current_camera_pos.y - screen_size.y/2);

      std::string stats = "";

      // render
      if (quadTreeMode) {
        auto objects_in_camera = qt_container.search(AreaRect(screen_pos, screen_size));
        for (auto& obj : objects_in_camera) obj->render(current_camera_pos, zoom);

        std::string objs_count_str = "\n" + std::to_string(objects_in_camera.size()) + " objects on screen";
        stats += objs_count_str;
      } else {
        for (auto& obj : objects) obj.render(current_camera_pos, zoom);
      }
      auto t2 = high_resolution_clock::now();
      std::chrono::duration<double> fp_ms = t2 - t1;

      text_bg.render();

      std::string mode = quadTreeMode ? "QuadTree" : "Linear";
      std::string current_mode = "\nCurrent mode: " + mode;
      std::string perf = "\nDelta time: " + std::to_string(fp_ms.count()) + "s";
      std::string cam_pos = "Camera {" + std::to_string(current_camera_pos.x) + ", " + std::to_string(current_camera_pos.y) + "}";
      
      stats = cam_pos + current_mode + perf + stats;

      coords.setString(stats);
      window.draw(coords);

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
