#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <iostream>

#include "../include/Physics.h"

int main() {
  sf::RenderWindow window(sf::VideoMode({1024, 900}), "Flappy Bird",
                          sf::Style::Close | sf::Style::Titlebar);

  Object new_object(200.f, 200.f, 100);
  Vector2D force = {0, 9.81};
  sf::CircleShape circle(50.f);
  circle.setFillColor(sf::Color(100, 250, 50));
  circle.setPosition({200.f, 100.f});

  float time = 0;
  while (window.isOpen()) {
    time += 0.1;
    new_object.apply_force(force);
    Vector2D new_position = new_object.get_postion(time);
    std::cout << "Acceleration: " << new_object.acceleration.x << ";"
              << new_object.acceleration.y << std::endl;
    std::cout << "Position: " << new_position.x << ";" << new_position.y
              << std::endl;
    circle.setPosition({new_position.x, new_position.y});
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }
    window.clear(sf::Color::Black);
    window.draw(circle);
    window.display();
  }
  return 0;
}
