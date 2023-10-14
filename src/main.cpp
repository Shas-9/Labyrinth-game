#include <SFML/Graphics.hpp>

#include "UI.h"
#include "Vector.h"
#include "Environment.h"

int main() {
  Vector vector = Vector(1000, 800);
  UI* ui = new UI(vector);

  ui->fetchHighScores();

  return 0;
}