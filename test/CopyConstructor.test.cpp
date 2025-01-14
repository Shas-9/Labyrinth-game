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

  bool is_rect;
  Vector velocity;
  sf::Shape* shape;
};

template <typename T>
struct QuadItem {
  T item;
};

int main() {
  list<QuadItem<DynamicCastObj>> container;

  DynamicCastObj obj(Vector(123, 123), Vector(123, 123));
  
  QuadItem<DynamicCastObj> new_item;
  new_item.item = obj;
  
  std::cout << obj.is_rect << "\n"; // outputs 1
  std::cout << obj.shape->getPosition().x << "\n"; // outputs 123

  std::cout << new_item.item.is_rect << "\n"; // outputs 1
  std::cout << new_item.item.shape->getPosition().x << "\n"; // outputs 123

  // issue happens here! new_item.item is not copied properly
  container.push_back(new_item);

  // 
  std::cout << container.back().item.is_rect << "\n"; // outputs 0
  std::cout << container.back().item.shape->getPosition().x << "\n"; // Segmentation fault (core dumped)
}