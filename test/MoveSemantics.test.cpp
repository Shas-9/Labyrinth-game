#include <SFML/Graphics.hpp>

#include "../src/Vector.h"
#include "../src/AreaShape.h"
#include "../src/singleton/ScreenManager.h"

#include <iterator>
#include <iostream>
#include <vector>
#include <list>

using std::list;

#define SCREEN_X ScreenManager::getInstance().screen_dimensions.x
#define SCREEN_Y ScreenManager::getInstance().screen_dimensions.y

// Move Semantics
struct MoveSemanticsObj {
  MoveSemanticsObj(Vector pos = { 0, 0 }, Vector dim = { 1, 1 }, const sf::Color color = sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256), Vector velocity = Vector(std::rand() % 11 - 5, std::rand() % 11 - 5)) {
    this->shape = new sf::RectangleShape();
    this->is_rect = true;
    this->velocity = velocity;
    this->pos = pos;
    this->dim = dim;

    auto rect = dynamic_cast<sf::RectangleShape*>(this->shape);
    rect->setFillColor(color);
    rect->setSize(sf::Vector2f(dim.x, dim.y));
    rect->setPosition(sf::Vector2f(pos.x, pos.y));
  }
  MoveSemanticsObj(Vector pos, double radius, const sf::Color color = sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256), Vector velocity = Vector(std::rand() % 11 - 5, std::rand() % 11 - 5)) {
    this->shape = new sf::CircleShape();
    this->is_rect = false;
    this->velocity = velocity;
    this->pos = pos;
    this->radius = radius;

    auto circ = dynamic_cast<sf::CircleShape*>(this->shape);
    circ->setFillColor(color);
    circ->setRadius(radius);
    circ->setPosition(sf::Vector2f(pos.x, pos.y));
  }
  void render(Vector current_camera_pos, float zoom) {
    if (this->is_rect == true) {
      Vector relative_pos = (Vector(this->getPos()) - current_camera_pos) * zoom + Vector(SCREEN_X, SCREEN_Y) / 2;
      auto rect = dynamic_cast<sf::RectangleShape*>(this->shape);

      rect->setPosition(sf::Vector2f(relative_pos.x, relative_pos.y));
      rect->setSize(sf::Vector2f(this->getDim().x, this->getDim().y) * zoom);
    } else if (this->is_rect == false) {
      Vector relative_pos = (Vector(this->getPos()) - current_camera_pos) * zoom + Vector(SCREEN_X, SCREEN_Y) / 2;
      auto circ = dynamic_cast<sf::CircleShape*>(this->shape);

      circ->setPosition(sf::Vector2f(relative_pos.x, relative_pos.y));
      circ->setRadius(this->getRadius() * zoom);
    }
    ScreenManager::getInstance().window_ptr->draw(*this->shape);
  }
  void render() {
    ScreenManager::getInstance().window_ptr->draw(*this->shape);
  }
  ~MoveSemanticsObj() { delete this->shape; }

  // Disable Copy Constructor and Copy Assignment Operator
  MoveSemanticsObj(const MoveSemanticsObj&) = delete;
  MoveSemanticsObj& operator=(const MoveSemanticsObj&) = delete;

  // Move Constructor
  MoveSemanticsObj(MoveSemanticsObj&& other) noexcept : shape(other.shape), is_rect(other.is_rect), velocity(other.velocity), pos(other.pos), dim(other.dim), radius(other.radius) {
    other.shape = nullptr; // Transfer ownership
  }

  // Move Assignment Operator
  MoveSemanticsObj& operator=(MoveSemanticsObj&& other) noexcept {
    if (this != &other) {
      delete this->shape;      // Clean up existing shape
      this->shape = other.shape; // Transfer ownership
      other.shape = nullptr;

      this->is_rect = other.is_rect;
      this->velocity = other.velocity;
      this->pos = other.pos;
      this->dim = other.dim;
      this->radius = other.radius;
    }
    return *this;
  }

  void setFillColor(sf::Color color) { this->shape->setFillColor(color); }
  sf::Shape* getShape() { return this->shape; }
  Vector getPos() { return Vector(this->pos); }
  void setPos(Vector new_pos) { this->pos = new_pos; }
  Vector getDim() { return this->dim; }
  float getRadius() { return this->radius; }

  bool is_rect;
  Vector velocity;
  Vector pos;
  Vector dim;
  float radius;
  sf::Shape* shape;
};


template <typename T>
struct QuadItem {
  T item;
};

int main() {
  list<QuadItem<MoveSemanticsObj>> container;

  MoveSemanticsObj obj(Vector(123, 123), Vector(123, 123));
  
  QuadItem<MoveSemanticsObj> new_item;
  new_item.item = std::move(obj);;
  
  std::cout << obj.is_rect << "\n"; // outputs 1
  std::cout << obj.getPos().x << "\n"; // outputs 123

  std::cout << new_item.item.is_rect << "\n"; // outputs 1
  std::cout << new_item.item.getPos().x << "\n"; // outputs 123

  // issue happens here! new_item.item is not copied properly
  container.push_back(std::move(new_item));

  // 
  std::cout << container.back().item.is_rect << "\n"; // outputs 0
  std::cout << container.back().item.getPos().x << "\n"; // Segmentation fault (core dumped)
}