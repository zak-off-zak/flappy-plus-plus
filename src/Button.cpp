#include "../include/Button.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

Button::Button()
    : shape(), text(this->font), font(), on_click([]() {}) {
  // Set up a default white button in the top left corner of the screen with the
  // size of 100 by 50
  this->shape.setPosition({0.f, 0.f});
  this->shape.setSize({100.f, 50.f});
  this->shape.setFillColor(sf::Color::White);
}

Button::Button(const Button &other)
    : shape(other.shape), on_click(other.on_click), text(other.text),
      font(other.font) {}

Button::Button(const sf::Vector2f &position,
                           const sf::Vector2f &size,
                           const sf::RectangleShape &shape,
                           const sf::Color &color, const sf::Text &text,
                           const sf::Font &font, unsigned int font_size,
                           const std::function<void()> &on_click)
    : shape(shape), text(font), on_click(on_click) {
  // Set the position, size and color of the custom buttons shape
  this->shape.setPosition(position);
  this->shape.setSize(size);
  this->shape.setFillColor(color);

  this->text = text;
  this->text.setFont(font);
  this->text.setCharacterSize(font_size);
  this->place_text();
}

void Button::handle_event(const std::optional<sf::Event> &event,
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

void Button::draw(sf::RenderTarget &target,
                        sf::RenderStates states) const {
  target.draw(shape, states);
  target.draw(this->text, states);
}

sf::Vector2f Button::getSize() { return this->shape.getSize(); }

void Button::setPosition(sf::Vector2f new_position) {
  this->shape.setPosition(new_position);
  this->place_text();
}

void Button::place_text() {
  this->text.setPosition(
      {this->shape.getPosition().x + ((this->shape.getLocalBounds().size.x -
                                       this->text.getLocalBounds().size.x) /
                                      2.f),
       this->shape.getPosition().y + this->text.getLocalBounds().size.y / 2.f});
}
