#include "../src/PerformanceTester.tpp"
#include "../src/QuadTree.tpp"
#include "../src/singleton/ScreenManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <iostream>
#include <vector>
#include <list>

using std::list;

#define SCREEN_X ScreenManager::getInstance().screen_dimensions.x
#define SCREEN_Y ScreenManager::getInstance().screen_dimensions.y

// Data Oreaitned Obj
struct DataOrientedObj {
  DataOrientedObj(Vector pos = { 0, 0 }, Vector dim = { 1, 1 }, const sf::Color color = sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256), Vector velocity = Vector(std::rand() % 11 - 5, std::rand() % 11 - 5)) {
    this->velocity = velocity;
    this->color = color;
    this->pos = pos;
    this->dim = dim;
  }
  DataOrientedObj(Vector pos, double radius, const sf::Color color = sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256), Vector velocity = Vector(std::rand() % 11 - 5, std::rand() % 11 - 5)) {
    this->velocity = velocity;
    this->color = color;
    this->pos = pos;
    this->radius = radius;
  }

  sf::Color color;
  Vector velocity;
  Vector pos;
  Vector dim;
  float radius;
};

struct OldObj {
  OldObj(Vector pos = { 0, 0 }, Vector dim = { 1, 1 }, const sf::Color color = sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256)) : pos(pos), dim(dim) {
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


struct Obj {
  Obj(Vector pos = { 0, 0 }, Vector dim = { 1, 1 }, const sf::Color color = sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256), Vector velocity = Vector(std::rand() % 11 - 5, std::rand() % 11 - 5)) : pos(pos), dim(dim) {
    this->type = 0;

    this->rectangle.setFillColor(color);

    // Set the size of the object
    this->rectangle.setSize(sf::Vector2f(this->dim.x, this->dim.y));

    // Set the position of the object
    this->rectangle.setPosition(sf::Vector2f(this->pos.x, this->pos.y));

    this->velocity = velocity;
  }
  Obj(Vector pos, double radius, const sf::Color color = sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256), Vector velocity = Vector(std::rand() % 11 - 5, std::rand() % 11 - 5)) : pos(pos), radius(radius) {
    this->type = 1;

    this->circle.setFillColor(color);

    // Set the size of the object
    this->circle.setRadius(radius);

    // Set the position of the object
    this->circle.setPosition(sf::Vector2f(this->pos.x, this->pos.y));

    this->velocity = velocity;
  }
  void render(Vector current_camera_pos, double zoom) {
    if (type == 0) {
      // update position with respect to zoom and camera
      Vector relative_pos = (this->pos - current_camera_pos) * zoom + Vector(SCREEN_X, SCREEN_Y) / 2;
      this->rectangle.setPosition(sf::Vector2f(relative_pos.x, relative_pos.y));
      this->rectangle.setSize(sf::Vector2f(this->dim.x * zoom, this->dim.y * zoom));

      (*ScreenManager::getInstance().window_ptr).draw(this->rectangle);
    } else if (type == 1) {
      // update position with respect to zoom and camera
      Vector relative_pos = (this->pos - current_camera_pos) * zoom + Vector(SCREEN_X, SCREEN_Y) / 2;
      this->circle.setPosition(sf::Vector2f(relative_pos.x, relative_pos.y));
      this->circle.setRadius(this->radius * zoom);

      (*ScreenManager::getInstance().window_ptr).draw(this->circle);
    }
  }
  void render() {
    if (type == 0) {
      this->rectangle.setPosition(sf::Vector2f(this->pos.x, this->pos.y));
      this->rectangle.setSize(sf::Vector2f(this->dim.x, this->dim.y));

      (*ScreenManager::getInstance().window_ptr).draw(this->rectangle);
    } else if (type == 1) {
      this->circle.setPosition(sf::Vector2f(this->pos.x, this->pos.y));
      this->circle.setRadius(this->radius);

      (*ScreenManager::getInstance().window_ptr).draw(this->circle);
    }
  }
  sf::Shape* getShape() {
    if (type == 0) return &this->rectangle;
    else if (type == 1) return &this->circle;
  }
  int type; // 0 = rect, 1 = circle
  Vector dim;
  Vector pos;
  Vector velocity;
  double radius;
  sf::RectangleShape rectangle;
  sf::CircleShape circle;
};

struct DynamicCastObj {
  DynamicCastObj(Vector pos = { 0, 0 }, Vector dim = { 1, 1 }, const sf::Color color = sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256), Vector velocity = Vector(std::rand() % 11 - 5, std::rand() % 11 - 5)) {
    this->shape = new sf::RectangleShape();
    this->is_rect = true;
    this->velocity = velocity;

    auto rect = dynamic_cast<sf::RectangleShape*>(this->shape);
    rect->setFillColor(color);
    rect->setSize(sf::Vector2f(dim.x, dim.y));
    rect->setPosition(sf::Vector2f(pos.x, pos.y));
  }
  DynamicCastObj(Vector pos, double radius, const sf::Color color = sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256), Vector velocity = Vector(std::rand() % 11 - 5, std::rand() % 11 - 5)) {
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
      rect->setPosition(sf::Vector2f(relative_pos.x, relative_pos.y));
      rect->setSize(rect->getSize() * zoom);
    } else if (this->is_rect == false) {
      Vector relative_pos = (Vector(this->shape->getPosition()) - current_camera_pos) * zoom + Vector(SCREEN_X, SCREEN_Y) / 2;
      auto circ = dynamic_cast<sf::CircleShape*>(this->shape);
      circ->setPosition(sf::Vector2f(relative_pos.x, relative_pos.y));
      circ->setRadius(circ->getRadius() * zoom);
    }
    ScreenManager::getInstance().window_ptr->draw(*this->shape);
  }
  void render() {
    ScreenManager::getInstance().window_ptr->draw(*this->shape);
  }
  ~DynamicCastObj() { delete this->shape; }

  // Copy Constructor (Deep Copy)
  DynamicCastObj(const DynamicCastObj& other) {
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
  DynamicCastObj& operator=(const DynamicCastObj& other) {
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

template <typename AREA_RECT_CONTAINER, typename OBJ_CONTAINER, typename OBJ_TYPE>
void constructQuadTree(QuadTreeContainer<OBJ_TYPE, AreaRect>& qt_container, AreaRect& qt_area, AREA_RECT_CONTAINER& rects, OBJ_CONTAINER& objs) {
  qt_container.resize(qt_area);
  // for (int i = 0; i < rects.size(); i++) qt_container.insert(objs[i], rects[i]);
  auto rects_it = rects.begin();
  auto objs_it = objs.begin();
  for (; rects_it != rects.end(); objs_it++, rects_it++) qt_container.insert(*objs_it, *rects_it);
}

template <typename AREA_CIRC_CONTAINER, typename OBJ_CONTAINER, typename OBJ_TYPE>
void constructQuadTree(QuadTreeContainer<OBJ_TYPE, AreaCirc>& qt_container, AreaRect& qt_area, AREA_CIRC_CONTAINER& circs, OBJ_CONTAINER& objs) {
  qt_container.resize(qt_area);
  // for (int i = 0; i < circs.size(); i++) qt_container.insert(objs[i], circs[i]);
  auto circs_it = circs.begin();
  auto objs_it = objs.begin();
  for (; circs_it != circs.end(); objs_it++, circs_it++) qt_container.insert(*objs_it, *circs_it);
}

template <typename AREA_RECT_CONTAINER>
void generateBoxes(AREA_RECT_CONTAINER& boxes, AreaRect bounds, int num_boxes) {
  for (int i = 0; i < num_boxes; i++) {
    int box_width = 50 + (std::rand() % 50 + 1);
    int box_height = 50 + (std::rand() % 50 + 1);
    int box_x = bounds.pos.x + std::rand() % (int)(bounds.size.x + 1 - box_width);
    int box_y = bounds.pos.y + std::rand() % (int)(bounds.size.y + 1 - box_height);
    boxes.push_back(AreaRect(box_x, box_y, box_width, box_height));
  }
}

template <typename AREA_CIRC_CONTAINER>
void generateCircles(AREA_CIRC_CONTAINER& circles, AreaRect bounds, int num_circles) {
  for (int i = 0; i < num_circles; i++) {
    int radius = 50 + (std::rand() % 50 + 1);
    int x = bounds.pos.x + std::rand() % (int)(bounds.size.x + 1 - radius);
    int y = bounds.pos.y + std::rand() % (int)(bounds.size.y + 1 - radius);
    circles.push_back(AreaCirc(x, y, radius));
  }
}

template <typename OBJ_TYPE>
void makeRectQuadTree(QuadTreeContainer<OBJ_TYPE, AreaRect>& qt_container, AreaRect bounds, int num) {
  qt_container.resize(bounds);

  for (int i = 0; i < num; i++) {
    int box_width = 50 + (std::rand() % 50 + 1);
    int box_height = 50 + (std::rand() % 50 + 1);
    int box_x = bounds.pos.x + std::rand() % (int)(bounds.size.x + 1 - box_width);
    int box_y = bounds.pos.y + std::rand() % (int)(bounds.size.y + 1 - box_height);
    
    qt_container.insert(
      OBJ_TYPE(Vector(box_x, box_y), Vector(box_width, box_height)), AreaRect(box_x, box_y, box_width, box_height)
    );
  }
}

template <typename OBJ_TYPE>
void makeCircQuadTree(QuadTreeContainer<OBJ_TYPE, AreaCirc>& qt_container, AreaRect bounds, int num) {
  qt_container.resize(bounds);

  for (int i = 0; i < num; i++) {
    int radius = 50 + (std::rand() % 50 + 1);
    int x = bounds.pos.x + std::rand() % (int)(bounds.size.x + 1 - radius);
    int y = bounds.pos.y + std::rand() % (int)(bounds.size.y + 1 - radius);

    qt_container.insert(
      OBJ_TYPE(Vector(x, y), radius), AreaCirc(x, y, radius)
    );
  }
}

// void testFuncVector(int num_boxes_circles) {
//   AreaRect map_boundary(0, 0, 15000, 15000);
//   Obj map_boundary_obj(map_boundary.pos, map_boundary.size);

//   vector<AreaRect> rects;
//   generateBoxes(rects, map_boundary, num_boxes_circles);

//   vector<AreaCirc> circs;
//   generateCircles(circs, map_boundary, num_boxes_circles);

//   vector<Obj> objects = {};
//   vector<Obj> rect_objects = {};
//   vector<Obj> circ_objects = {};

//   for (const auto& rect : rects) { objects.push_back(Obj(rect.pos, rect.size)); rect_objects.push_back(Obj(rect.pos, rect.size)); }
//   for (const auto& circ : circs) { objects.push_back(Obj(circ.pos, circ.radius)); circ_objects.push_back(Obj(circ.pos, circ.radius)); }

//   QuadTreeContainer<Obj, AreaRect> qt_container_rect;
//   constructQuadTree(qt_container_rect, map_boundary, rects, rect_objects);

//   QuadTreeContainer<Obj, AreaCirc> qt_container_circ;
//   constructQuadTree(qt_container_circ, map_boundary, circs, circ_objects);

//   // for (int frame = 0; i < 100; frame++) {

//   // }
// }

// void testFuncList(int num_boxes_circles) {
//   AreaRect map_boundary(0, 0, 15000, 15000);
//   Obj map_boundary_obj(map_boundary.pos, map_boundary.size);

//   list<AreaRect> rects;
//   generateBoxes(rects, map_boundary, num_boxes_circles);

//   list<AreaCirc> circs;
//   generateCircles(circs, map_boundary, num_boxes_circles);

//   list<Obj> objects = {};
//   list<Obj> rect_objects = {};
//   list<Obj> circ_objects = {};

//   for (const auto& rect : rects) { objects.push_back(Obj(rect.pos, rect.size)); rect_objects.push_back(Obj(rect.pos, rect.size)); }
//   for (const auto& circ : circs) { objects.push_back(Obj(circ.pos, circ.radius)); circ_objects.push_back(Obj(circ.pos, circ.radius)); }

//   QuadTreeContainer<Obj, AreaRect> qt_container_rect;
//   constructQuadTree(qt_container_rect, map_boundary, rects, rect_objects);

//   QuadTreeContainer<Obj, AreaCirc> qt_container_circ;
//   constructQuadTree(qt_container_circ, map_boundary, circs, circ_objects);

//   // for (int frame = 0; i < 100; frame++) {

//   // }
// }

struct TestObj {
  // Constructor
  TestObj(Vector pos = { 0, 0 }, Vector dim = { 1, 1 }) {
    this->shape = new sf::RectangleShape();
    auto rect = dynamic_cast<sf::RectangleShape*>(this->shape);
    rect->setSize(sf::Vector2f(dim.x, dim.y));
    rect->setPosition(sf::Vector2f(pos.x, pos.y));
  }

  // Destructor
  ~TestObj() { delete this->shape; }

  // Copy Constructor (Deep Copy)
  TestObj(const TestObj& other) {
    if (auto rect = dynamic_cast<sf::RectangleShape*>(other.shape)) {
      this->shape = new sf::RectangleShape(*rect); // Deep copy the RectangleShape
    } else {
      this->shape = nullptr; // Handle other types of shapes if applicable
    }
  }

  // Copy Assignment Operator (Deep Copy)
  TestObj& operator=(const TestObj& other) {
    if (this != &other) {
      delete this->shape; // Clean up existing resource

      // Deep copy the shape
      if (auto rect = dynamic_cast<sf::RectangleShape*>(other.shape)) {
        this->shape = new sf::RectangleShape(*rect);
      } else {
        this->shape = nullptr;
      }
    }
    return *this;
  }

  sf::Shape* shape;
};

void testFuncVectorDynamicCastObj(int num_boxes_circles) {
  AreaRect map_boundary(0, 0, 15000, 15000);
  DynamicCastObj map_boundary_obj(map_boundary.pos, map_boundary.size);

  vector<AreaRect> rects;
  generateBoxes(rects, map_boundary, num_boxes_circles);

  vector<AreaCirc> circs;
  generateCircles(circs, map_boundary, num_boxes_circles);


  vector<DynamicCastObj> objects = {};
  vector<DynamicCastObj> rect_objects = {};
  vector<DynamicCastObj> circ_objects = {};

  for (const auto& rect : rects) { objects.push_back(DynamicCastObj(rect.pos, rect.size)); rect_objects.push_back(DynamicCastObj(rect.pos, rect.size)); }
  // std::cout << "things have not generated" << std::endl;
  for (const auto& circ : circs) { objects.push_back(DynamicCastObj(circ.pos, circ.radius)); circ_objects.push_back(DynamicCastObj(circ.pos, circ.radius)); }

  QuadTreeContainer<DynamicCastObj, AreaRect> qt_container_rect;
  constructQuadTree(qt_container_rect, map_boundary, rects, rect_objects);

  QuadTreeContainer<DynamicCastObj, AreaCirc> qt_container_circ;
  constructQuadTree(qt_container_circ, map_boundary, circs, circ_objects);
}

void testFuncVectorDynamicCastObjOptimized(int num_boxes_circles) {
  AreaRect map_boundary(0, 0, 15000, 15000);
  DynamicCastObj map_boundary_obj(map_boundary.pos, map_boundary.size);

  QuadTreeContainer<DynamicCastObj, AreaRect> qt_container_rect;
  makeRectQuadTree(qt_container_rect, map_boundary, num_boxes_circles);

  QuadTreeContainer<DynamicCastObj, AreaCirc> qt_container_circ;
  makeCircQuadTree(qt_container_circ, map_boundary, num_boxes_circles);
}

void testFuncVectorDataOrientedObj(int num_boxes_circles) {
  AreaRect map_boundary(0, 0, 15000, 15000);
  DataOrientedObj map_boundary_obj(map_boundary.pos, map_boundary.size);

  QuadTreeContainer<DataOrientedObj, AreaRect> qt_container_rect;
  makeRectQuadTree(qt_container_rect, map_boundary, num_boxes_circles);

  QuadTreeContainer<DataOrientedObj, AreaCirc> qt_container_circ;
  makeCircQuadTree(qt_container_circ, map_boundary, num_boxes_circles);
}

// void testFuncVectorTestObj(int num_boxes_circles) {
//   AreaRect map_boundary(0, 0, 15000, 15000);
//   TestObj map_boundary_obj(map_boundary.pos, map_boundary.size);

//   vector<AreaRect> rects;
//   generateBoxes(rects, map_boundary, num_boxes_circles);

//   vector<AreaCirc> circs;
//   generateCircles(circs, map_boundary, num_boxes_circles);


//   vector<TestObj> objects = {};
//   vector<TestObj> rect_objects = {};
//   vector<TestObj> circ_objects = {};

//   for (const auto& rect : rects) { objects.push_back(TestObj(rect.pos, rect.size)); rect_objects.push_back(TestObj(rect.pos, rect.size)); }
//   // std::cout << "things have not generated" << std::endl;
//   // for (const auto& circ : circs) { objects.push_back(TestObj(circ.pos, circ.radius)); circ_objects.push_back(TestObj(circ.pos, circ.radius)); }

//   QuadTreeContainer<TestObj, AreaRect> qt_container_rect;
//   constructQuadTree(qt_container_rect, map_boundary, rects, rect_objects);

//   // QuadTreeContainer<TestObj, AreaCirc> qt_container_circ;
//   // constructQuadTree(qt_container_circ, map_boundary, circs, circ_objects);

//   // vector<TestObj> objects = {};
//   // objects.push_back(std::move(map_boundary_obj));
// }

// void testFuncVectorOldObj(int num_boxes_circles) {
//   AreaRect map_boundary(0, 0, 15000, 15000);
//   OldObj map_boundary_obj(map_boundary.pos, map_boundary.size);

//   vector<AreaRect> rects;
//   generateBoxes(rects, map_boundary, num_boxes_circles);

//   vector<AreaCirc> circs;
//   generateCircles(circs, map_boundary, num_boxes_circles);


//   vector<OldObj> objects = {};
//   vector<OldObj> rect_objects = {};
//   vector<OldObj> circ_objects = {};

//   for (const auto& rect : rects) { objects.push_back(OldObj(rect.pos, rect.size)); rect_objects.push_back(OldObj(rect.pos, rect.size)); }
//   // std::cout << "things have not generated" << std::endl;
//   // for (const auto& circ : circs) { objects.push_back(OldObj(circ.pos, circ.radius)); circ_objects.push_back(OldObj(circ.pos, circ.radius)); }

//   QuadTreeContainer<OldObj, AreaRect> qt_container_rect;
//   constructQuadTree(qt_container_rect, map_boundary, rects, rect_objects);

//   // QuadTreeContainer<OldObj, AreaCirc> qt_container_circ;
//   // constructQuadTree(qt_container_circ, map_boundary, circs, circ_objects);

//   // vector<OldObj> objects = {};
//   // objects.push_back(std::move(map_boundary_obj));
// }

int main() {
  PerformanceTester<int> perf;
  std::cout << "sf::RectangleShape: " << sizeof(sf::RectangleShape) << std::endl;
  std::cout << "sf::CircleShape: " << sizeof(sf::CircleShape) << std::endl;
  std::cout << "Obj: " << sizeof(Obj) << std::endl;
  std::cout << "OldObj: " << sizeof(OldObj) << std::endl;
  std::cout << "Vector: " << sizeof(Vector) << std::endl;
  std::cout << "sf::Shape*: " << sizeof(sf::Shape*) << std::endl;
  std::cout << "DynamicCastObj: " << sizeof(DynamicCastObj) << std::endl;
  std::cout << "TestObj: " << sizeof(TestObj) << std::endl;
  std::cout << "Vector: " << sizeof(Vector) << std::endl;
  std::cout << "sf::Color: " << sizeof(sf::Color) << std::endl;
  std::cout << "float: " << sizeof(float) << std::endl;
  std::cout << "DataOrientedObj: " << sizeof(DataOrientedObj) << std::endl;
  std::cout << perf.testVariableFuncMeanPerf(&testFuncVectorDynamicCastObjOptimized, 50000, 1) << std::endl;
  // std::cout << perf.testVariableFuncMeanPerf(&testFuncVectorDataOrientedObj, 50000, 1) << std::endl;
  // std::cout << perf.testVariableFuncMeanPerf(&testFuncVectorDynamicCastObj, 50000, 5) << std::endl;
  // perf.plotFuncPerf("number of boxes+circles", testFuncVectorDynamicCastObjOptimized, 1, 500, 1000000, 2, false);
}