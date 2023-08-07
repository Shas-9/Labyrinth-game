#include <SFML/Graphics.hpp>
#include <iostream>

#include "test.h"

extern void printHello();

int main()
{
    printHello();
    std::cout << "App is running" << std::endl;
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(20, 300);
    std::cout << "THE CIRCLE IS AT " << shape.getPosition().x << std::endl;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
