#include "Obstacle.h"

Obstacle::Obstacle(Vector position, string type, Vector dimensions)
    : RenderedObject(position, type), dimensions(dimensions) {}

// Obstacle update function should do nothing.
void Obstacle::update() {}

void Obstacle::render() {
  // Render
}