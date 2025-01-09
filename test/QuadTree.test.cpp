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


struct Obj {
  Obj(Vector pos = {0, 0}, Vector dim = {1, 1}, const sf::Color color = sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256), Vector velocity = Vector(std::rand() % 11 - 5, std::rand() % 11 - 5)) : pos(pos), dim(dim) {
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

template <typename AREA_RECT_CONTAINER, typename OBJ_CONTAINER>
void constructQuadTree(QuadTreeContainer<Obj, AreaRect>& qt_container, AreaRect& qt_area, AREA_RECT_CONTAINER& rects, OBJ_CONTAINER& objs) {
  qt_container.resize(qt_area);
  // for (int i = 0; i < rects.size(); i++) qt_container.insert(objs[i], rects[i]);
  auto rects_it = rects.begin();
  auto objs_it = objs.begin();
  for(; rects_it != rects.end(); objs_it++, rects_it++) qt_container.insert(*objs_it, *rects_it);
}

template <typename AREA_CIRC_CONTAINER, typename OBJ_CONTAINER>
void constructQuadTree(QuadTreeContainer<Obj, AreaCirc>& qt_container, AreaRect& qt_area, AREA_CIRC_CONTAINER& circs, OBJ_CONTAINER& objs) {
  qt_container.resize(qt_area);
  // for (int i = 0; i < circs.size(); i++) qt_container.insert(objs[i], circs[i]);
  auto circs_it = circs.begin();
  auto objs_it = objs.begin();
  for(; circs_it != circs.end(); objs_it++, circs_it++) qt_container.insert(*objs_it, *circs_it);
}

template <typename AREA_RECT_CONTAINER>
void generateBoxes(AREA_RECT_CONTAINER& boxes, AreaRect bounds, int num_boxes) {
  for (int i = 0; i < num_boxes; i++) {
    int box_width = 50 + (std::rand() % 50+1);
    int box_height = 50 + (std::rand() % 50+1);
    int box_x = bounds.pos.x + std::rand() % (int)(bounds.size.x + 1 - box_width);
    int box_y = bounds.pos.y + std::rand() % (int)(bounds.size.y + 1 - box_height);
    boxes.push_back(AreaRect(box_x, box_y, box_width, box_height));
  }
}

template <typename AREA_CIRC_CONTAINER>
void generateCircles(AREA_CIRC_CONTAINER& circles, AreaRect bounds, int num_circles) {
  for (int i = 0; i < num_circles; i++) {
    int radius = 50 + (std::rand() % 50+1);
    int x = bounds.pos.x + std::rand() % (int)(bounds.size.x + 1 - radius);
    int y = bounds.pos.y + std::rand() % (int)(bounds.size.y + 1 - radius);
    circles.push_back(AreaCirc(x, y, radius));
  }
}

void testFuncVector(int num_boxes_circles) {
  AreaRect map_boundary(0, 0, 15000, 15000);
  Obj map_boundary_obj(map_boundary.pos, map_boundary.size);

  vector<AreaRect> rects;
  generateBoxes(rects, map_boundary, num_boxes_circles);

  vector<AreaCirc> circs;
  generateCircles(circs, map_boundary, num_boxes_circles);

  vector<Obj> objects = {};
  vector<Obj> rect_objects = {};
  vector<Obj> circ_objects = {};

  for (const auto& rect : rects) { objects.push_back(Obj(rect.pos, rect.size)); rect_objects.push_back(Obj(rect.pos, rect.size)); }
  for (const auto& circ : circs) { objects.push_back(Obj(circ.pos, circ.radius)); circ_objects.push_back(Obj(circ.pos, circ.radius)); }
  
  QuadTreeContainer<Obj, AreaRect> qt_container_rect;
  constructQuadTree(qt_container_rect, map_boundary, rects, rect_objects);

  QuadTreeContainer<Obj, AreaCirc> qt_container_circ;
  constructQuadTree(qt_container_circ, map_boundary, circs, circ_objects);

  // for (int frame = 0; i < 100; frame++) {

  // }
}

void testFuncList(int num_boxes_circles) {
  AreaRect map_boundary(0, 0, 15000, 15000);
  Obj map_boundary_obj(map_boundary.pos, map_boundary.size);

  list<AreaRect> rects;
  generateBoxes(rects, map_boundary, num_boxes_circles);

  list<AreaCirc> circs;
  generateCircles(circs, map_boundary, num_boxes_circles);

  list<Obj> objects = {};
  list<Obj> rect_objects = {};
  list<Obj> circ_objects = {};

  for (const auto& rect : rects) { objects.push_back(Obj(rect.pos, rect.size)); rect_objects.push_back(Obj(rect.pos, rect.size)); }
  for (const auto& circ : circs) { objects.push_back(Obj(circ.pos, circ.radius)); circ_objects.push_back(Obj(circ.pos, circ.radius)); }
  
  QuadTreeContainer<Obj, AreaRect> qt_container_rect;
  constructQuadTree(qt_container_rect, map_boundary, rects, rect_objects);

  QuadTreeContainer<Obj, AreaCirc> qt_container_circ;
  constructQuadTree(qt_container_circ, map_boundary, circs, circ_objects);

  // for (int frame = 0; i < 100; frame++) {

  // }
}

int main() {
  PerformanceTester<int> perf;
  // std::cout << perf.testFuncMeanPerf(&testFunc, 1) << std::endl;
  perf.plotFuncPerf("number of boxes+circles", testFuncVector, 1, 500, 1000000, 2, false);
}