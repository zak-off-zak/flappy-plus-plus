#include "../include/CustomButton.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

CustomButton::CustomButton() : shape(), on_click([]() {}) {
  // Set up a default white button in the top left corner of the screen with the
  // size of 100 by 50
  this->shape.setPosition({0.f, 0.f});
  this->shape.setSize({100.f, 50.f});
  this->shape.setFillColor(sf::Color::White);
}

CustomButton::CustomButton(const CustomButton &other)
    : shape(other.shape), on_click(other.on_click) {}

CustomButton::CustomButton(const sf::Vector2f &position,
                           const sf::Vector2f &size,
                           const sf::RectangleShape &shape,
                           const sf::Color &color,
                           const std::function<void()> &on_click)
    : shape(shape), on_click(on_click) {
  // Set the position, size and color of the custom buttons shape
  this->shape.setPosition(position);
  this->shape.setSize(size);
  this->shape.setFillColor(color);
}

void CustomButton::handle_event(const std::optional<sf::Event> &event,
                                const sf::RenderWindow &window) {
  // Check if the left button of the mouse has been pressed
  if (event->is<sf::Event::MouseButtonPressed>() &&
      sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
    // Get the position of the mouse
    sf::Vector2f mouse_position =
        window.mapPixelToCoords({sf::Mouse::getPosition(window)});
    // If the mouse position is inside the custom button, trigger the on_click()
    // function
    if (this->shape.getGlobalBounds().contains(mouse_position)) {
      this->on_click();
    }
  }
}

void CustomButton::draw(sf::RenderTarget &target,
                        sf::RenderStates states) const {
  target.draw(shape, states);
}
