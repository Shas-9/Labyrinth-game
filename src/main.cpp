#include <SFML/Graphics.hpp>

#include "UI.h"
#include "Vector.h"
#include "Environment.h"

#include <iostream>

int main() {
  Vector vector = Vector(1920, 1080);
  // Vector vector = Vector(1366, 768);
  UI* ui = new UI(vector);

  return 0;
}
