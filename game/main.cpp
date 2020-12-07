#include <iostream>
#include "SFML/Graphics.hpp"
#include <box2d/box2d.h>


int main() {
    b2World World(b2Vec2(0.0, 0.0));

    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Test");
    window.setFramerateLimit(60);

    while (window.isOpen()){
        window.clear();
        window.display();
    }

    return 0;
}
