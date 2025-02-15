#include "../include/GameLoop.h"
#include "../include/Bird.h"
#include <SFML/Graphics/RenderWindow.hpp>

void game_loop(sf::RenderWindow &window, Bird &bird, float &time) {
  while (window.isOpen()) {
    time += 0.1;
    bird.update_position(time);
    while (const std::optional event = window.pollEvent()) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        bird.flap();
      }
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }
    window.clear(sf::Color::Black);
    bird.draw(window);
    window.display();
  }
}
