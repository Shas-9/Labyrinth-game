#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <chrono>
using namespace std::chrono_literals;

#include "UI.h"
#include "singleton/ScreenManager.h"

#include "QuadTree.tpp"
#include <ctime>
#include <cmath>
#include <iostream>

#define SCREEN_X ScreenManager::getInstance().screen_dimensions.x
#define SCREEN_Y ScreenManager::getInstance().screen_dimensions.y

struct Obj {
  Obj(Vector pos = {0, 0}, Vector dim = {1, 1}, const sf::Color color = sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256)) : pos(pos), dim(dim) {
    // this->rectangle = new sf::RectangleShape();
    this->rectangle.setFillColor(color);

    // Set the size of the object
    this->rectangle.setSize(sf::Vector2f(this->dim.x, this->dim.y));

    // Set the position of the object
    this->rectangle.setPosition(sf::Vector2f(this->pos.x, this->pos.y));

    this->velocity = Vector(std::rand() % 11 - 5, std::rand() % 11 - 5);
  }
  void render(Vector current_camera_pos, double zoom) {
    // update position with respect to zoom and camera
    Vector relative_pos = (this->pos - current_camera_pos) * zoom + Vector(SCREEN_X, SCREEN_Y) / 2;
    this->rectangle.setPosition(sf::Vector2f(relative_pos.x, relative_pos.y));
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
  Vector velocity;
  sf::RectangleShape rectangle;
};

void constructQuadTree(DynamicQuadTreeContainer<Obj>& qt_container, AreaRect& qt_area, vector<AreaRect>& rects, vector<Obj>& objs) {
  qt_container.resize(qt_area);
  for (int i = 0; i < rects.size(); i++) qt_container.insert(objs[i], rects[i]);
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

void drawGrid(sf::RenderWindow& win, int rows, int cols, Vector current_camera_pos, double zoom, const AreaRect& map_boundary) {
    // initialize values
    int numLines = rows+cols-2;
    sf::VertexArray grid(sf::Lines, 2*(numLines));
    // win.setView(win.getDefaultView());
    // auto size = win.getView().getSize();
    Vector size = map_boundary.size;
    // size.x *= 15000;
    // size.y *= 15000;
    float rowH = size.y/rows;
    float colW = size.x/cols;
    // row separators
    for(int i=0; i < rows-1; i++){
        int r = i+1;
        float rowY = rowH*r;

        Vector pos_vec1 = {0.0f, rowY};
        Vector relative_pos1 = (pos_vec1 - current_camera_pos) * zoom + Vector(SCREEN_X, SCREEN_Y) / 2;
        grid[i*2].position = {static_cast<float>(relative_pos1.x), static_cast<float>(relative_pos1.y)};

        Vector pos_vec2 = {static_cast<float>(size.x), rowY};
        Vector relative_pos2 = (pos_vec2 - current_camera_pos) * zoom + Vector(SCREEN_X, SCREEN_Y) / 2;
        grid[i*2+1].position = {static_cast<float>(relative_pos2.x), static_cast<float>(relative_pos2.y)};
    }
    // column separators
    for(int i=rows-1; i < numLines; i++){
        int c = i-rows+2;
        float colX = colW*c;
        
        Vector pos_vec1 = {colX, 0.0f};
        Vector relative_pos1 = (pos_vec1 - current_camera_pos) * zoom + Vector(SCREEN_X, SCREEN_Y) / 2;
        grid[i*2].position = {static_cast<float>(relative_pos1.x), static_cast<float>(relative_pos1.y)};

        Vector pos_vec2 = {colX, static_cast<float>(size.y)};
        Vector relative_pos2 = (pos_vec2 - current_camera_pos) * zoom + Vector(SCREEN_X, SCREEN_Y) / 2;
        grid[i*2+1].position = {static_cast<float>(relative_pos2.x), static_cast<float>(relative_pos2.y)};
    }
    // draw it
    win.draw(grid);
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

    DynamicQuadTreeContainer<Obj> qt_container;
    constructQuadTree(qt_container, map_boundary, rects, objects);
    
    qt_container.visualizeTree("testing/static-quad-tree.dot"); 

    Vector target_camera_pos(0, 0);
    double zoom = 1 * SCREEN_Y/1080;

    Vector current_camera_pos(0, 0);

    sf::Font font;
    font.loadFromFile("fonts/MouldyCheese.ttf");

    sf::Text coords;
    coords.setFont(font);
    coords.setCharacterSize(24);
    coords.setPosition(10, 10);

    bool mouse_pressed = false;
    Vector old_mouse_pos = Vector(10000, 10000);
    
    bool quadTreeMode = true;
    bool remove_objects_in_cursor = false;

    Obj text_bg(Vector(0, 0), Vector(480, 130), sf::Color(1, 1, 1, 150));

    sf::Event event;
    Vector mouse_pos(0, 0);
    Obj cursor_box(Vector(0, 0), Vector(0, 0));

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::seconds;

    sf::Clock deltaClock;

    std::chrono::duration<double> delta_time;

    // Screen loop
    while (window.isOpen()) {
      sf::Time deltaTime = deltaClock.restart();
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
          if (event.mouseButton.button == sf::Mouse::Right) remove_objects_in_cursor = true;
          break;
        case sf::Event::MouseButtonReleased:
          if (event.mouseButton.button == sf::Mouse::Left) {
            mouse_pressed = false;
            old_mouse_pos = Vector(10000, 10000);
          }
          if (event.mouseButton.button == sf::Mouse::Right) remove_objects_in_cursor = false;
          break;

        case sf::Event::MouseMoved: 
          mouse_pos = Vector(event.mouseMove.x, event.mouseMove.y);
          if (mouse_pressed) {
            if (old_mouse_pos == Vector(10000, 10000)) 
              old_mouse_pos = Vector(event.mouseMove.x, event.mouseMove.y);

            Vector delta = old_mouse_pos - Vector(event.mouseMove.x, event.mouseMove.y);
            target_camera_pos += delta/zoom;

            old_mouse_pos = Vector(event.mouseMove.x, event.mouseMove.y);
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

      Vector screen_size = Vector(SCREEN_X, SCREEN_Y)/zoom;
      Vector rendering_distance = screen_size*3;
      Vector screen_pos = current_camera_pos - screen_size/2;

      cursor_box = Obj((mouse_pos - Vector(SCREEN_X, SCREEN_Y)/2 - Vector(50, 50))/zoom + current_camera_pos, Vector(50, 50)*2/zoom, sf::Color(255, 255, 255, 80));

      std::string stats = "";

      drawGrid(window, 50, 50, current_camera_pos, zoom, map_boundary);

      // render
      if (quadTreeMode) {

        if (remove_objects_in_cursor) {
          auto objects_in_cursor = qt_container.search(AreaRect(cursor_box.pos, cursor_box.dim));
          for (auto& obj : objects_in_cursor) qt_container.remove(obj);
        }

        auto objects_in_camera = qt_container.search(AreaRect(screen_pos, rendering_distance));
        for (auto& obj : objects_in_camera) {
          obj->item.render(current_camera_pos, zoom);
          obj->item.pos += obj->item.velocity * 100 * deltaTime.asSeconds();
          qt_container.relocate(obj, AreaRect(obj->item.pos, obj->item.dim));
        }

        std::string objs_count_str = "\n" + std::to_string(objects_in_camera.size()) + " objects on screen";
        stats += objs_count_str;
      } else {
        for (auto& obj : objects) obj.render(current_camera_pos, zoom);
      }
      auto t2 = high_resolution_clock::now();
      delta_time = t2 - t1;

      cursor_box.render(current_camera_pos, zoom);

      text_bg.render();

      std::string mode = quadTreeMode ? "QuadTree" : "Linear";
      std::string current_mode = "\nCurrent mode: " + mode;
      std::string perf = "\nDelta time: " + std::to_string(delta_time.count()) + "s";
      std::string framerate = "\nFramerate delta: " + std::to_string(deltaTime.asSeconds()) + "s";
      std::string cam_pos = "Camera {" + std::to_string(current_camera_pos.x) + ", " + std::to_string(current_camera_pos.y) + "}";
      
      stats = cam_pos + current_mode + perf + framerate + stats;

      coords.setString(stats);
      window.draw(coords);

      window.display();
    }
  }
};

int main() {
  srand(time(0));
  UI* ui = new UI();
  // UI* ui = new UI(800, 500);
  // UI* ui = new UI(1920/4, 1080/4);
  // CamTesting *test = new CamTesting();
  // CamTesting *test = new CamTesting(1920/1.7, 1080/1.7);
  

  return 0;
}
