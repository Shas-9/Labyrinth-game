#include <iostream>

#include "UI.h"

// int main() {
//   sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
//   sf::CircleShape shape(100.f);
//   shape.setFillColor(sf::Color::Green);
//   shape.setPosition(20, 300);
//   std::cout << "THE CIRCLE IS AT " << shape.getPosition().x << std::endl;

//   while (window.isOpen()) {
//     sf::Event event;
//     while (window.pollEvent(event)) {
//       if (event.type == sf::Event::Closed) window.close();
//     }

//     window.clear();
//     window.draw(shape);
//     window.display();
//   }

//   return 0;
// }

int main() {
  UI ui_object(600, 600);

  return 0;
}
