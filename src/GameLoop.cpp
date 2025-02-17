#include "../include/GameLoop.h"
#include "../include/Bird.h"
#include <SFML/Graphics/RenderWindow.hpp>

void game_loop(sf::RenderWindow &window, Bird &bird, float &time) {
  while (window.isOpen()) {
    time += 0.00001;
    bird.update_sprite(time);
    bool spaceWasPressed = false;
    while (const std::optional event = window.pollEvent()) {
      bool spaceIsPressed =
          sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
      if (spaceIsPressed && !spaceWasPressed) {
        bird.flap(time, window);
      }
      spaceWasPressed = spaceIsPressed;
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }
    window.clear(sf::Color::Black);
    bird.draw(window);
    window.display();
  }
}
