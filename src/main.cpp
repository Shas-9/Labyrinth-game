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

// struct Obj {
//   Obj(Vector pos = {0, 0}, Vector dim = {1, 1}, const sf::Color color = sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256), Vector velocity = Vector(std::rand() % 11 - 5, std::rand() % 11 - 5)) : pos(pos), dim(dim) {
//     this->type = 0;

//     this->rectangle.setFillColor(color);

//     // Set the size of the object
//     this->rectangle.setSize(sf::Vector2f(this->dim.x, this->dim.y));

//     // Set the position of the object
//     this->rectangle.setPosition(sf::Vector2f(this->pos.x, this->pos.y));

//     this->velocity = velocity;
//   }
//   Obj(Vector pos, double radius, const sf::Color color = sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256), Vector velocity = Vector(std::rand() % 11 - 5, std::rand() % 11 - 5)) : pos(pos), radius(radius) {
//     this->type = 1;

//     this->circle.setFillColor(color);

//     // Set the size of the object
//     this->circle.setRadius(radius);

//     // Set the position of the object
//     this->circle.setPosition(sf::Vector2f(this->pos.x, this->pos.y));

//     this->velocity = velocity;
//   }
//   void render(Vector current_camera_pos, double zoom) {
//     if (type == 0) {
//       // update position with respect to zoom and camera
//       Vector relative_pos = (this->pos - current_camera_pos) * zoom + Vector(SCREEN_X, SCREEN_Y) / 2;
//       this->rectangle.setPosition(sf::Vector2f(relative_pos.x, relative_pos.y));
//       this->rectangle.setSize(sf::Vector2f(this->dim.x * zoom, this->dim.y * zoom));
      
//       (*ScreenManager::getInstance().window_ptr).draw(this->rectangle);
//     } else if (type == 1) {
//       // update position with respect to zoom and camera
//       Vector relative_pos = (this->pos - current_camera_pos) * zoom + Vector(SCREEN_X, SCREEN_Y) / 2;
//       this->circle.setPosition(sf::Vector2f(relative_pos.x, relative_pos.y));
//       this->circle.setRadius(this->radius * zoom);
      
//       (*ScreenManager::getInstance().window_ptr).draw(this->circle);
//     }
//   }
//   void render() {
//     if (type == 0) {
//       this->rectangle.setPosition(sf::Vector2f(this->pos.x, this->pos.y));
//       this->rectangle.setSize(sf::Vector2f(this->dim.x, this->dim.y));
      
//       (*ScreenManager::getInstance().window_ptr).draw(this->rectangle);
//     } else if (type == 1) {
//       this->circle.setPosition(sf::Vector2f(this->pos.x, this->pos.y));
//       this->circle.setRadius(this->radius);
      
//       (*ScreenManager::getInstance().window_ptr).draw(this->circle);
//     }
//   }
//   sf::Shape* getShape() {
//     if (type == 0) return &this->rectangle;
//     else if (type == 1) return &this->circle;
//   }
//   int type; // 0 = rect, 1 = circle
//   Vector dim;
//   Vector pos;
//   Vector velocity;
//   double radius;
//   sf::RectangleShape rectangle;
//   sf::CircleShape circle;
// };

struct Obj {
  Obj(Vector pos = { 0, 0 }, Vector dim = { 1, 1 }, const sf::Color color = sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256), Vector velocity = Vector(std::rand() % 11 - 5, std::rand() % 11 - 5)) {
    this->shape = new sf::RectangleShape();
    this->is_rect = true;
    this->velocity = velocity;

    auto rect = dynamic_cast<sf::RectangleShape*>(this->shape);
    rect->setFillColor(color);
    rect->setSize(sf::Vector2f(dim.x, dim.y));
    rect->setPosition(sf::Vector2f(pos.x, pos.y));
  }
  Obj(Vector pos, double radius, const sf::Color color = sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256), Vector velocity = Vector(std::rand() % 11 - 5, std::rand() % 11 - 5)) {
    this->shape = new sf::CircleShape();
    this->is_rect = false;
    this->velocity = velocity;

    auto circ = dynamic_cast<sf::CircleShape*>(this->shape);
    circ->setFillColor(color);
    circ->setRadius(radius);
    circ->setPosition(sf::Vector2f(pos.x, pos.y));
  }
  void render(Vector current_camera_pos, float zoom) {
    if (this->is_rect == true) {
      Vector relative_pos = (Vector(this->shape->getPosition()) - current_camera_pos) * zoom + Vector(SCREEN_X, SCREEN_Y) / 2;
      auto rect = dynamic_cast<sf::RectangleShape*>(this->shape);
      
      sf::Vector2f old_pos = rect->getPosition();
      sf::Vector2f old_dim = rect->getSize();

      rect->setPosition(sf::Vector2f(relative_pos.x, relative_pos.y));
      rect->setSize(rect->getSize() * zoom);
      
      ScreenManager::getInstance().window_ptr->draw(*this->shape);

      rect->setPosition(old_pos);
      rect->setSize(old_dim);
    } else if (this->is_rect == false) {
      Vector relative_pos = (Vector(this->shape->getPosition()) - current_camera_pos) * zoom + Vector(SCREEN_X, SCREEN_Y) / 2;
      auto circ = dynamic_cast<sf::CircleShape*>(this->shape);
      
      sf::Vector2f old_pos = circ->getPosition();
      float old_radius = circ->getRadius();

      circ->setPosition(sf::Vector2f(relative_pos.x, relative_pos.y));
      circ->setRadius(circ->getRadius() * zoom);
      
      ScreenManager::getInstance().window_ptr->draw(*this->shape);

      circ->setPosition(old_pos);
      circ->setRadius(old_radius);
    }
  }
  void render() {
    ScreenManager::getInstance().window_ptr->draw(*this->shape);
  }
  ~Obj() { delete this->shape; }

  // Copy Constructor (Deep Copy)
  Obj(const Obj& other) {
    this->is_rect = other.is_rect;
    this->velocity = other.velocity;

    if (this->is_rect) {
      if (auto rect = dynamic_cast<sf::RectangleShape*>(other.shape)) {
        this->shape = new sf::RectangleShape(*rect); // Deep copy the RectangleShape
      } else {
        this->shape = nullptr; // Handle other types of shapes if applicable
      }
    } else {
      if (auto circ = dynamic_cast<sf::CircleShape*>(other.shape)) {
        this->shape = new sf::CircleShape(*circ); // Deep copy the RectangleShape
      } else {
        this->shape = nullptr; // Handle other types of shapes if applicable
      }
    }
  }

  // Copy Assignment Operator (Deep Copy)
  Obj& operator=(const Obj& other) {
    if (this != &other) {
      delete this->shape; // Clean up existing resource

      this->is_rect = other.is_rect;
      this->velocity = other.velocity;

      // Deep copy the shape
      if (this->is_rect) {
        if (auto rect = dynamic_cast<sf::RectangleShape*>(other.shape)) {
          this->shape = new sf::RectangleShape(*rect); // Deep copy the RectangleShape
        } else {
          this->shape = nullptr; // Handle other types of shapes if applicable
        }
      } else {
        if (auto circ = dynamic_cast<sf::CircleShape*>(other.shape)) {
          this->shape = new sf::CircleShape(*circ); // Deep copy the RectangleShape
        } else {
          this->shape = nullptr; // Handle other types of shapes if applicable
        }
      }
    }
    return *this;
  }

  void setFillColor(sf::Color color) { this->shape->setFillColor(color); }
  sf::Shape* getShape() { return this->shape; }
  Vector getPos() { return Vector(this->shape->getPosition()); }
  void setPos(Vector new_pos) { this->shape->setPosition(new_pos.x, new_pos.y); }
  Vector getDim() {
    if (this->is_rect) {
      auto rect = dynamic_cast<sf::RectangleShape*>(this->shape);
      return Vector(rect->getSize());
    } else return Vector(0, 0);
  }
  float getRadius() {
    if (this->is_rect) return 0;
    else {
      auto circ = dynamic_cast<sf::CircleShape*>(this->shape);
      return circ->getRadius();
    }
  }

  bool is_rect;
  Vector velocity;
  sf::Shape* shape;
};

void constructQuadTree(QuadTreeContainer<Obj, AreaRect>& qt_container, AreaRect& qt_area, vector<AreaRect>& rects, vector<Obj>& objs) {
  qt_container.resize(qt_area);
  for (int i = 0; i < rects.size(); i++) qt_container.insert(objs[i], rects[i]);
}

void constructQuadTree(QuadTreeContainer<Obj, AreaCirc>& qt_container, AreaRect& qt_area, vector<AreaCirc>& circs, vector<Obj>& objs) {
  qt_container.resize(qt_area);
  for (int i = 0; i < circs.size(); i++) qt_container.insert(objs[i], circs[i]);
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

void generateCircles(vector<AreaCirc>& circles, AreaRect bounds, int num_circles) {
  for (int i = 0; i < num_circles; i++) {
    int radius = 50 + (std::rand() % 50+1);
    int x = bounds.pos.x + std::rand() % (int)(bounds.size.x + 1 - radius);
    int y = bounds.pos.y + std::rand() % (int)(bounds.size.y + 1 - radius);
    circles.push_back(AreaCirc(x, y, radius));
  }
}

void drawGrid(sf::RenderWindow& win, int rows, int cols, Vector current_camera_pos, double zoom, const AreaRect& map_boundary) {
    // initialize values
    int numLines = rows+cols-2;
    sf::VertexArray grid(sf::Lines, 2*(numLines));
    Vector size = map_boundary.size;
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

    AreaRect map_boundary(0, 0, 1500, 1500);
    Obj map_boundary_obj(map_boundary.pos, map_boundary.size);

    vector<AreaRect> rects;
    generateBoxes(rects, map_boundary, 250);

    vector<AreaCirc> circs;
    generateCircles(circs, map_boundary, 250);

    vector<Obj> objects = {};
    vector<Obj> rect_objects = {};
    vector<Obj> circ_objects = {};

    for (const auto& rect : rects) { objects.push_back(Obj(rect.pos, rect.size)); rect_objects.push_back(Obj(rect.pos, rect.size)); }
    for (const auto& circ : circs) { objects.push_back(Obj(circ.pos, circ.radius)); circ_objects.push_back(Obj(circ.pos, circ.radius)); }

    QuadTreeContainer<Obj, AreaRect> qt_container_rect;
    constructQuadTree(qt_container_rect, map_boundary, rects, rect_objects);

    QuadTreeContainer<Obj, AreaCirc> qt_container_circ;
    constructQuadTree(qt_container_circ, map_boundary, circs, circ_objects);
    
    // qt_container_rect.visualizeTree("testing/static-quad-tree.dot"); 

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

    Obj text_bg(Vector(0, 0), Vector(500, 130), sf::Color(1, 1, 1, 150));

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
      Vector new_cam_pos = Vector::getMid(current_camera_pos, target_camera_pos, 10.0);
      current_camera_pos = new_cam_pos;

      // // instant caera movement
      // current_camera_pos = target_camera_pos;

      Vector screen_size = Vector(SCREEN_X, SCREEN_Y)/zoom;
      Vector rendering_distance = screen_size*3;
      Vector screen_pos = current_camera_pos - screen_size/2;

      cursor_box = Obj((mouse_pos - Vector(SCREEN_X, SCREEN_Y)/2 - Vector(50, 50))/zoom + current_camera_pos, Vector(50, 50)*2/zoom, sf::Color(255, 255, 255, 80));
      Obj cursor_circ = Obj((mouse_pos - Vector(SCREEN_X, SCREEN_Y)/2 - Vector(50, 50))/zoom + current_camera_pos, 50/zoom, sf::Color(255, 255, 0, 80));
      Obj test_box = Obj(Vector(0, 0), Vector(100, 200), sf::Color(255, 100, 0));
      Obj test_circ = Obj(Vector(300, 0), 40, sf::Color(255, 100, 0));

      std::string stats = "";

      drawGrid(window, 50, 50, current_camera_pos, zoom, map_boundary);

      // render
      if (quadTreeMode) {

        if (remove_objects_in_cursor) {
          auto circ_objects_in_cursor = qt_container_circ.search(AreaRect(cursor_box.getPos(), cursor_box.getDim()));
          for (auto& circ_obj : circ_objects_in_cursor) qt_container_circ.remove(circ_obj);

          auto rect_objects_in_cursor = qt_container_rect.search(AreaRect(cursor_box.getPos(), cursor_box.getDim()));
          for (auto& rect_obj : rect_objects_in_cursor) qt_container_rect.remove(rect_obj);
        }

        auto circ_objects_in_camera = qt_container_circ.search(AreaRect(screen_pos, rendering_distance));
        auto rect_objects_in_camera = qt_container_rect.search(AreaRect(screen_pos, rendering_distance));

        for (auto& obj : circ_objects_in_camera) {
          // move object
          // std::cout << obj->item.is_rect << std::endl;
          // obj->item.setPos(obj->item.getPos() + obj->item.velocity * 100 * deltaTime.asSeconds());
          // qt_container_circ.relocate(obj, AreaCirc(obj->item.getPos(), obj->item.getRadius()));
          // // setFillColor upon collision
          if (qt_container_circ.search(AreaCirc(obj->item.getPos(), obj->item.getRadius())).size() > 1) obj->item.getShape()->setFillColor(sf::Color(255, 255, 255));
          else if (qt_container_rect.search(AreaCirc(obj->item.getPos(), obj->item.getRadius())).size() > 0) obj->item.getShape()->setFillColor(sf::Color(255, 255, 255));
          else obj->item.getShape()->setFillColor(sf::Color(100, 100, 255));
          // render
          obj->item.render(current_camera_pos, zoom);
        }

        for (auto& obj : rect_objects_in_camera) {
          // move object
          // obj->item.getPos() += obj->item.velocity * 100 * deltaTime.asSeconds();
          // qt_container_rect.relocate(obj, AreaRect(obj->item.getPos(), obj->item.getDim()));
          // setFillColor upon collision
          if (qt_container_rect.search(AreaRect(obj->item.getPos(), obj->item.getDim())).size() > 1) obj->item.getShape()->setFillColor(sf::Color(255, 255, 255));
          else if (qt_container_circ.search(AreaRect(obj->item.getPos(), obj->item.getDim())).size() > 0) obj->item.getShape()->setFillColor(sf::Color(255, 255, 255));
          else obj->item.getShape()->setFillColor(sf::Color(100, 100, 255));
          // render
          obj->item.render(current_camera_pos, zoom);
        }

        std::string objs_count_str = "\n" + std::to_string(rect_objects_in_camera.size() + circ_objects_in_camera.size()) + " objects on screen";
        stats += objs_count_str;
      } else {
        for (auto& obj : objects) obj.render(current_camera_pos, zoom);
      }
      auto t2 = high_resolution_clock::now();
      delta_time = t2 - t1;

      cursor_box.render(current_camera_pos, zoom);
      cursor_circ.render(current_camera_pos, zoom);
      
      if (AreaRect(test_box.getPos(), test_box.getDim()).overlap(AreaCirc(cursor_circ.getPos(), cursor_circ.getRadius()))) test_box.setFillColor(sf::Color(255, 255, 255));
      else test_box.setFillColor(sf::Color(255, 100, 0));
      test_box.render(current_camera_pos, zoom);
      
      // if (AreaCirc(test_circ.getPos(), test_circ.getRadius()).contains(AreaCirc(cursor_circ.getPos(), cursor_circ.getRadius()))) test_circ.setFillColor(sf::Color(255, 255, 255));
      // else test_circ.setFillColor(sf::Color(255, 100, 0));
      test_circ.render(current_camera_pos, zoom);

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
  // UI* ui = new UI();
  // UI* ui = new UI(800, 500);
  // UI* ui = new UI(1920/4, 1080/4);
  CamTesting *test = new CamTesting();
  // CamTesting *test = new CamTesting(1920/1.7, 1080/1.7);
  

  return 0;
}
