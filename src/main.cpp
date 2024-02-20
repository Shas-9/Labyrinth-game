#include <SFML/Graphics.hpp>

#include "UI.hpp"
#include "Vector.hpp"
#include "Environment.hpp"

#include <iostream>

int main() {
  Vector vector = Vector(1920, 1080);
  UI* ui = new UI(vector);

  return 0;
}