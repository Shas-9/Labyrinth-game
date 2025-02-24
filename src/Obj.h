#include "singleton/ScreenManager.h"

#define SCREEN_X ScreenManager::getInstance().screen_dimensions.x
#define SCREEN_Y ScreenManager::getInstance().screen_dimensions.y

// Deep copy
struct DeepCopyObj {
  DeepCopyObj(Vector pos = { 0, 0 }, Vector dim = { 1, 1 }, const sf::Color color = sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256), Vector velocity = Vector(std::rand() % 11 - 5, std::rand() % 11 - 5)) {
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
  DeepCopyObj(Vector pos, double radius, const sf::Color color = sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256), Vector velocity = Vector(std::rand() % 11 - 5, std::rand() % 11 - 5)) {
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
  ~DeepCopyObj() { delete this->shape; }

  // Copy Constructor (Deep Copy)
  DeepCopyObj(const DeepCopyObj& other) {
    this->is_rect = other.is_rect;
    this->velocity = other.velocity;
    this->pos = other.pos;
    this->dim = other.dim;
    this->radius = other.radius;

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
  DeepCopyObj& operator=(const DeepCopyObj& other) {
    if (this != &other) {
      delete this->shape; // Clean up existing resource

      this->is_rect = other.is_rect;
      this->velocity = other.velocity;
      this->pos = other.pos;
      this->dim = other.dim;
      this->radius = other.radius;

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


#define Obj DataOrientedObj