#include <SFML/Graphics.hpp>

#include "UI.h"
#include "Vector.h"
#include "Environment.h"

#include <iostream>

int main() {
  Vector vector = Vector(1000, 800);
  UI* ui = new UI(vector);

  ui->pushHighScore();

  return 0;
}