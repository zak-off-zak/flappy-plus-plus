#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode({512, 512}), "Flappy Bird",
                          sf::Style::Close | sf::Style::Titlebar);

  sf::CircleShape circle(50.f);
  circle.setFillColor(sf::Color(100, 250, 50));
  circle.setPosition({200.f, 200.f});

  while (window.isOpen()) {
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
